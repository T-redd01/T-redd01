#include "main.h"

/* extra funcs */
void exec_func(char **vect) {
	int pid;

	pid = fork();
	if (pid == 0) {
		if ((execve(vect[0], vect, environ)) == -1) {
			perror("exec_func: execve");
			return;
		}
	} else {
		wait(NULL);
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

tokens *create_tok_node(char *inp, size_t idx) {
	size_t i, tmp = idx, len =0;
	char *val = NULL;
	tokens *new = NULL;

	if (!inp)
		return (NULL);

	new = malloc(sizeof(tokens));
	if (!new) {
		perror("create_tok_node: new");
		return (NULL);
	}

	while (!(find_delim(inp, tmp))) {
		tmp++;
		len++;
	}
	val = malloc((len + 1) * sizeof(char));
	if (!val) {
		free(new);
		perror("create_tok_node: val");
		return (NULL);
	}
	for (i = 0; !(find_delim(inp, idx)); i++, idx++)
		val[i] = inp[idx];
	val[i] = '\0';
	new->token = val;
	new->n = NULL;
	return (new);
}

tokens *create_delim_tok(char *input, size_t idx) {
	tokens *new = NULL;

	if (!input)
		return (NULL);

	new = malloc(sizeof(tokens));
	if (!new) {
		perror("create_delim_tok: new");
		return (NULL);
	}

	if (input[idx] == ';')
		new->token = _strdup(";");
	else if (input[idx] == '&' && input[idx + 1] == '&')
		new->token = _strdup("&&");
	else
		new->token = _strdup("||");
	new->n = NULL;
	return (new);
}

tokens *parser(char *input) {
	tokens *head = NULL, *new = NULL;
	size_t i;

	if (!input)
		return (NULL);

	for (i = 0; input[i]; i++) {
		if (!(find_delim(input, i))) {
			if (input[i] == '#')
				break;
			new = create_tok_node(input, i);
			append_tokens_node(&head, new);
			while (!(find_delim(input, i)))
				i++;
		}
		if ((find_delim(input, i))) {
			new = create_delim_tok(input, i);
			append_tokens_node(&head, new);
		}
		if (input[i] == '\0')
			i--;
	}
	return (head);
}

int main(__attribute__((unused)) int ac, __attribute__((unused)) char **av) {
	tokens *head = NULL;

	head = parser("");
	print_tokens_list(head);
	free_tokens_list(head);
	return (0);
}

