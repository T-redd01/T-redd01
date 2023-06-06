#include "main.h"

cmd_buf *create_cmd_buf_node(tokens *arg_strt, size_t arg_count)
{
	cmd_buf *new = NULL;
	int i = 0;
	char **arg_vec = NULL, symbol = '\0';

	if (!arg_strt || !arg_count)
		return (NULL);
	new = malloc(sizeof(cmd_buf));
	if (!new)
	{
		perror("cmd_buf malloc:");
		exit(98);
	}
	arg_vec = malloc((arg_count + 1) * sizeof(char *));
	if (!arg_vec)
	{
		perror("arg_vec malloc:");
		exit(98);
	}
	while (arg_strt && !(find_delim(arg_strt->token, 0)))
	{
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

cmd_buf *append_cmd_buf_node(cmd_buf **head, cmd_buf *node)
{
	cmd_buf *tmp = *head;

	if (!node)
		return (NULL);

	if (*head == NULL)
	{
		*head = node;
		return (node);
	}

	while (tmp->n_cmd)
		tmp = tmp->n_cmd;
	tmp->n_cmd = node;
	return (node);
}

cmd_buf *create_cmd_buf(tokens **h)
{
	size_t tok_count;
	tokens *tmp = *h, *tmp2 = NULL;
	cmd_buf *head = NULL, *node;

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
		node = create_cmd_buf_node(tmp2, tok_count);
		append_cmd_buf_node(&head, node);
		if (tmp)
			tmp = tmp->n;
	}
	return (head);
}

void print_cmd_list(cmd_buf *h)
{
	int i = 0, j = 0;

	if (!h)
		printf("h: nil\n");

	while (h)
	{
		i++;
		printf("node %d:\n", i);
		for (j = 0; h->args[j]; j++)
			printf("%d. %s\n", j + 1, h->args[j]);
		if (h->chain_symbol)
			printf("chain: %c\n", h->chain_symbol);
		else
			printf("chain: (nil)\n");
		printf("\n");
		h = h->n_cmd;
	}
}

void free_cmd_list(cmd_buf *h)
{
	int i;
	cmd_buf *tmp;

	if (!h)
		return;

	while (h)
	{
		tmp = h->n_cmd;
		for (i = 0; h->args[i]; i++)
			free(h->args[i]);
		free(h->args);
		free(h);
		h = tmp;
	}
}