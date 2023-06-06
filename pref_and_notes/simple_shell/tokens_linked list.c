#include "main.h"

tokens *add_tokens_node_end(tokens **head, char *src)
{
	tokens *new, *tmp = *head;

	if (!src)
		return (NULL);

	new = malloc(sizeof(tokens));
	if (new == NULL)
		return (NULL);
	new->token = _strdup(src);
	new->n = NULL;

	if (*head == NULL)
	{
		*head = new;
		return (new);
	}

	while (tmp->n)
		tmp = tmp->n;
	tmp->n = new;
	return (new);
}

void print_tokens_list(tokens *h)
{
	int node = 0;

	if (!h)
	{
		printf("head: (nil)\n");
		return;
	}

	while (h)
	{
		node++;
		printf("%d. %s\n", node, h->token);
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