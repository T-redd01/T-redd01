#include "main.h"

char *find_alias(al_list *h, tokens *n) {
	if (!h || !n)
		return (NULL);

	while (h) {
		if ((my_strcmp(h->name, n->token))) {
			free(n->token);
			n->token = _strdup(h->val);
			return (h->val);
		}
		h = h->n_al;
	}
	return (NULL);
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

tokens *create_delim_tok(char *input, size_t *idx) {
	tokens *new = NULL;

	if (!input)
		return (NULL);

	new = malloc(sizeof(tokens));
	if (!new) {
		perror("create_delim_tok: new");
		return (NULL);
	}

	if (input[*idx] == ';') {
		new->token = _strdup(";");
	}
	else if (input[*idx] == '&' && input[*idx + 1] == '&') {
		new->token = _strdup("&&");
		*idx += 1;
	}
	else if (input[*idx] == '|' && input[*idx + 1] == '|') {
		new->token = _strdup("||");
		*idx += 1;
	}
	else {
		free(new);
		return (NULL);
	}
	new->n = NULL;
	return (new);
}

cmds *parser(al_list *als, char *input) {
	tokens *head = NULL, *new = NULL;
	cmds *commands = NULL;
	size_t i;

	if (!input)
		return (NULL);

	for (i = 0; input[i]; i++) {
		if (!(find_delim(input, i))) {
			if (input[i] == '#')
				break;
			new = create_tok_node(input, i);
			exp_tok(new);
			append_tokens_node(&head, new);
			while (!(find_delim(input, i)))
				i++;
		}
		if ((find_delim(input, i))) {
			new = create_delim_tok(input, &i);
			append_tokens_node(&head, new);
		}
		if (input[i] == '\0')
			i--;
	}

	if (!head)
		return (NULL);

	commands = create_cmds_list(als, &head);
	free_tokens_list(head);
	return (commands);
}

