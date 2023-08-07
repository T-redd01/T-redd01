#include "lists.h"

listint_t *insert_node(listint_t **head, int number) {
	listint_t *new = NULL, *tmp = *head;

	new = malloc(sizeof(listint_t));
	if (!new)
		return (NULL);

	new->n = number;
	new->next = NULL;
	if (!tmp) {
		*head = new;
		return (new);
	}

	if (tmp->n > number) {
		new->next = *head;
		*head = new;
		return (new);
	}

	while (tmp->next && tmp->next->n < number)
		tmp = tmp->next;
	new->next = tmp->next;
	tmp->next = new;
	return (new);
}

