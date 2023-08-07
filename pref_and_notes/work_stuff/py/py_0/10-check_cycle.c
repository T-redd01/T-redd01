#include "lists.h"

/**
 * check_cycle - checks for cycle in linked list
 * @list: list to check
 *
 * Return: 0 if there is no cycle, 1 if there is
 */
int check_cycle(listint_t *list)
{
	listint_t *fast = list, *slow = list;

	if (!list)
		return (0);

	while (slow && fast->next && fast->next->next)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast)
			return (1);
	}
	return (0);
}

