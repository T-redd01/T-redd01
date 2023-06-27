#include "lists.h"

size_t print_list(const listint_t *h) {
	const listint *curr;
	size_t n;

	if (!h)
		return;

	curr = h;
	n = 0;
	while (current) {
		printf("%i\n", curr->num);
		curr = curr->n;
		n++;
	}
	return (n);
}

listint_t *add_nodeint(listint_t **head, const int n) {
	listint_t *new;

	new = malloc(sizeof(listint_t));
	if (!new)
		return (NULL);

	new->num = n;
	new->n = *head;
	*head = new;
	return (new);
}

void free_listint(listint_t *head) {
	listint_t *curr;

	if (!head)
		return;

	while (head) {
		curr = head;
		head = head->n;
		free(current);
	}
}

int check_cycle(listint_t *list) {
	/* check cycle here */
}
