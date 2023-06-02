#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern int errno;

typedef struct token_list {
	char *token;
	struct token_list *n;
} tokens;

typedef struct cmd_list {
	char **args;
	char chain_symbol;
	struct cmd_list *n_cmd;
} cmd_buf;

char *_strdup(char *src) {
	size_t len = 0;
	char *new;

	if (!src)
		return (NULL);

	while (src[len])
		len++;

	new = malloc((len + 1) * sizeof(char));
	if (new == NULL)
		return (NULL);
	for (len = 0; src[len]; len++)
		new[len] = src[len];
	new[len] ='\0';
	return (new);
}


tokens *add_tokens_node_end(tokens **head, char *src) {
	tokens *new, *tmp = *head;

	if (!src)
		return (NULL);

	new = malloc(sizeof(tokens));
	if (new == NULL)
		return (NULL);
	new->token = _strdup(src);
	new->n = NULL;

	if (*head == NULL) {
		*head = new;
		return (new);
	}

	while (tmp->n)
		tmp = tmp->n;
	tmp->n = new;
	return (new);
}

void print_tokens_list(tokens *h) {
	int node = 0;

	if (!h) {
		printf("head: (nil)\n");
		return;
	}

	while (h) {
		node++;
		printf("%d. %s\n", node, h->token);
		h = h->n;
	}
}

void free_tokens_list(tokens *h) {
	tokens *tmp;

	if (!h)
		return;

	while (h) {
		tmp = h->n;
		free(h->token);
		free(h);
		h = tmp;
	}
}

int find_delim(char *inp, size_t idx) {
	if (inp[idx] == '\0')
		return (1);
	else if (inp[idx] == ' ')
		return (1);
	else if (inp[idx] == ';')
		return (1);
	else if (inp[idx] == '&' && inp[idx + 1] == '&')
		return (1);
	else if (inp[idx] == '|' && inp[idx + 1] == '|')
		return (1);
	else if (inp[idx] == '\n')
		return (1);
	else
		return (0);
}

tokens *new_list(char *inp) {
	size_t i, bufidx = 0;
	char buffer[4096];
	tokens *head = NULL;

	if (!inp)
		return (NULL);

	for (i = 0; inp[i]; i++) {
		if (!(find_delim(inp, i))) {
			if (inp[i] == '#')
				break;
			bufidx = 0;
			while (!(find_delim(inp, i))) {
				buffer[bufidx++] = inp[i];
				i++;
			}
			buffer[bufidx] = '\0';
			add_tokens_node_end(&head, buffer);
			i--;
		}
		if (inp[i] == ';')
			add_tokens_node_end(&head, ";");
		if (inp[i] == '&' && inp[i + 1] == '&') {
			add_tokens_node_end(&head, "&&");
			i++;
		}
		if (inp[i] == '|' && inp[i + 1] == '|') {
			add_tokens_node_end(&head, "||");
			i++;
		}
		if (inp[i] == '\0')
			i--;
	}
	return (head);
}

void remove_node(tokens **h, int idx) {
	int i;
	tokens *tmp = *h, *to_rem;

	if (!(*h))
		return;

	if (idx == 0) {
		*h = tmp->n;
		free(tmp->token);
		free(tmp);
		return;
	}

	for (i = 0; i != (idx - 1) && tmp; i++)
		tmp = tmp->n;
	if (!tmp || !(tmp->n))
		return;
	to_rem = tmp->n;
	tmp->n = to_rem->n;
	if (!to_rem)
		return;
	free(to_rem->token);
	free(to_rem);
}

char *exp_var(char *s) {
	int i, j, buf_idx = 0;
	char buffer[4096], env[4096], *var = NULL;

	for (i = 0; s[i]; i++) {
		j = 0;
		if (s[i] == '$' && s[i + 1] == '$') {
			var = _strdup("1234");
			while (var[j])
				buffer[buf_idx++] = var[j++];
			i++;
			free(var);
		} else if (s[i] == '$' && s[i + 1] == '?') {
			var = _strdup("0");
			while (var[j])
				buffer[buf_idx++] = var[j++];
			i++;
			free(var);
		} else if (s[i] == '$' && (s[i + 1] == '\0' || s[i + 1] == '=')) {
			buffer[buf_idx++] = '$';
		} else if (s[i] == '$' && s[i + 1]) {
			i++;
			while (s[i] && s[i] != '=')
				env[j++] = s[i++];
			env[j] = '\0';
			i--;
			var = _strdup(getenv(env));
			if (var) {
				j = 0;
				while (var[j])
					buffer[buf_idx++] = var[j++];
			}
		} else {
			buffer[buf_idx++] = s[i];
		}
		if (s[i] == '\0')
			i--;
	}
	buffer[buf_idx] = '\0';
	if (buffer[0] == '\0')
		return (NULL);
	var = _strdup(buffer);
	return (var);
}

void find_var(tokens **head) {
	int i, idx = 0;
	char *new_str = NULL;
	tokens *tmp = *head, *move_to = NULL;

	if (!(*head))
		return;

	printf("\n");
	while (tmp) {
		move_to = tmp->n;
		for (i = 0; tmp->token[i]; i++) {
			if (tmp->token[i] == '$') {
				new_str = exp_var(tmp->token);
				if (new_str) {
					free(tmp->token);
					tmp->token = _strdup(new_str);
					free(new_str);
				} else {
					remove_node(head, idx);
					idx--;
				}
				break;
			}
		}
		idx++;
		tmp = move_to;
	}
}

cmd_buf *create_cmd_buf_node(tokens *arg_strt, size_t arg_count) {
	cmd_buf *new = NULL;
	int i = 0;
	char **arg_vec = NULL, symbol = '\0';

	if (!arg_strt || !arg_count)
		return (NULL);
	new = malloc(sizeof(cmd_buf));
	if (!new) {
		perror("cmd_buf malloc:");
		exit(98);
	}
	arg_vec = malloc((arg_count + 1) * sizeof(char *));
	if (!arg_vec) {
		perror("arg_vec malloc:");
		exit(98);
	}
	while (arg_strt && !(find_delim(arg_strt->token, 0))) {
		arg_vec[i++] = _strdup(arg_strt->token);
		arg_strt = arg_strt->n;
	}
	arg_vec[i] = NULL;

	new->args = arg_vec;
	if (arg_strt)
		symbol = arg_strt->token[0];
	new->chain_symbol = symbol;
	new->n_cmd = NULL;
	return (new);
}

cmd_buf *append_cmd_buf_node(cmd_buf **head, cmd_buf *node) {
	cmd_buf *tmp = *head;

	if (!node)
		return (NULL);

	if (*head == NULL) {
		*head = node;
		return (node);
	}

	while (tmp->n_cmd)
		tmp = tmp->n_cmd;
	tmp->n_cmd = node;
	return (node);
}

cmd_buf *create_cmd_buf(tokens **h) {
	size_t tok_count;
	tokens *tmp = *h, *tmp2 = NULL;
	cmd_buf *head = NULL, *node;

	if (!(*h))
		return (NULL);

	while (tmp) {
		tmp2 = tmp;
		tok_count = 0;
		node = NULL;
		while (tmp && !(find_delim(tmp->token, 0))) {
			tok_count++;
			tmp = tmp->n;
		}
		node = create_cmd_buf_node(tmp2, tok_count);
		append_cmd_buf_node(&head, node);
		if (tmp)
			tmp = tmp->n;
	}
	return (head);

}

void print_cmd_list(cmd_buf *h) {
	int i = 0, j = 0;

	if (!h)
		printf("h: nil\n");

	while (h) {
		i++;
		printf("node %d:\n", i);
		for (j = 0; h->args[i]; j++)
			printf("%d. %s\n", j + 1, h->args[j]);
		if (h->chain_symbol)
			printf("chain: %c\n", h->chain_symbol);
		else
			printf("chain: (nil)\n");
		printf("\n");
		h = h->n_cmd;
	}
}

void free_cmd_list(cmd_buf *h) {
	int i;
	cmd_buf *tmp;

	if (!h)
		return;

	while (h) {
		tmp = h->n_cmd;
		for (i = 0; h->args[i]; i++)
			free(h->args[i]);
		free(h->args);
		h = tmp;
	}
}

int exec_proc(char **args) {
	pid_t pid;

	pid = fork();
	if (pid == -1) {
		perror("Error fork:");
		return (-1);
	}

	if (pid == 0) {
		printf("child process: %d\n", getpid());
		if (execve(args[0], args, NULL) == -1) {
			perror("Error execve:");
			return (-1);
		}
	} else {
		wait(NULL);
		printf("Parent process: %d\n", getpid());
	}
	return (0);
}

int main(void) {
	char *inp = "; alias $=ls";
	tokens *head = NULL;
	cmd_buf *start = NULL;

	head = new_list(inp);
	printf("Before tokens:\n");
	print_tokens_list(head);

	find_var(&head);
	printf("\nAfter tokens:\n");
	print_tokens_list(head);

	start = create_cmd_buf(&head);
	printf("\nBefore cmd_list:\n");
	print_cmd_list(start);

/*	free_cmd_list(start);
	start = NULL;
	printf("\nFreed cmd_list:\n");
	print_cmd_list(start);
*/
	free_tokens_list(head);
	head = NULL;
	printf("\nFreed tokens:\n");
	print_tokens_list(head);
	return (0);
}

