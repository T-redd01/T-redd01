#include "main.h"

cmds *create_cmds_node(al_list *als, tokens *toks, size_t arg_count) {
	cmds *new = NULL;
	int i = 0;
	char **arg_vec = NULL, symbol = '\0';

	if (!toks || !arg_count)
		return (NULL);
	new = malloc(sizeof(cmds));
	if (!new) {
		perror("create_cmds_node: new");
		return (NULL);
	}
	arg_vec = malloc((arg_count + 1) * sizeof(char *));
	if (!arg_vec) {
		perror("create_cmds: arg_vec");
		free(new);
		return (NULL);
	}

	find_alias(als, toks);
	while (toks && !(find_delim(toks->token, 0))) {
		arg_vec[i++] = _strdup(toks->token);
		toks = toks->n;
	}
	arg_vec[i] = NULL;

	new->vect = arg_vec;
	if (toks)
		symbol = toks->token[0];
	new->sym = symbol;
	new->n = NULL;
	return (new);
}

cmds *append_cmds_node(cmds **head, cmds *node)
{
	cmds *tmp = *head;

	if (!node)
		return (NULL);

	if (*head == NULL)
	{
		*head = node;
		return (node);
	}

	while (tmp->n)
		tmp = tmp->n;
	tmp->n = node;
	return (node);
}

cmds *create_cmds_list(al_list *als, tokens **h)
{
	size_t tok_count;
	tokens *tmp = *h, *tmp2 = NULL;
	cmds *head = NULL, *node;

	if (!(*h))
		return (NULL);

	while (tmp)
	{
		tmp2 = tmp;
		tok_count = 0;
		node = NULL;
		while (tmp && !(find_delim(tmp->token, 0)))
		{
			tok_count++;
			tmp = tmp->n;
		}
		node = create_cmds_node(als, tmp2, tok_count);
		append_cmds_node(&head, node);
		if (tmp)
			tmp = tmp->n;
	}
	return (head);
}

void print_cmds_list(cmds *h)
{
	size_t i = 0, j = 0;
	char *num = NULL;

	if (!h)
		_puts("h: nil\n", 1);

	while (h)
	{
		i++;
		_puts("node ", 1);
		num = _itoa(i);
		_puts(num, 1);
		free(num);
		_puts(":\n", 1);
		for (j = 0; h->vect[j]; j++) {
			num = _itoa(j + 1);
			_puts(num, 1);
			free(num);
			_puts(h->vect[j], 1);
			_puts("\n", 1);
		}
		if (h->sym) {
			_puts("chain: ", 1);
			_putchar(h->sym);
			_puts("\n", 1);
		}
		else {
			_puts("chain: (nil)\n", 1);
		}
		_puts("\n", 1);
		h = h->n;
	}
}

void free_cmds_list(cmds *h)
{
	int i;
	cmds *tmp;

	if (!h)
		return;

	while (h)
	{
		tmp = h->n;
		for (i = 0; h->vect[i]; i++)
			free(h->vect[i]);
		free(h->vect);
		free(h);
		h = tmp;
	}
}

