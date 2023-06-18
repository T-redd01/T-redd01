#include "main.h"

void remove_node(tokens **h, int idx)
{
	int i;
	tokens *tmp = *h, *to_rem;

	if (!(*h))
		return;

	if (idx == 0)
	{
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

void append_tokens_node(tokens **head, tokens *node) {
	tokens *tmp = *head;

	if (!node)
		return;

	if (*head == NULL) {
		*head = node;
		return;
	}

	while (tmp->n)
		tmp = tmp->n;
	tmp->n = node;
	return;
}

void print_tokens_list(tokens *h)
{
	if (!h) {
		_puts("head: (nil)\n", 1);
		return;
	}

	while (h) {
		_puts(h->token, 1);
		_puts("\n", 1);
		h = h->n;
	}
}

void free_tokens_list(tokens *h)
{
	tokens *tmp;

	if (!h)
		return;

	while (h)
	{
		tmp = h->n;
		free(h->token);
		free(h);
		h = tmp;
	}
}

