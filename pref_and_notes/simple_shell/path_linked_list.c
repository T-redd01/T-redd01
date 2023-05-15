#include "main.h"

void print_path_list(path_list **h)
{
	path_list *tmp = *h;

	if (!*h)
		return;

	while (tmp)
	{
		printf("%s->%d\n", tmp->bin_paths, tmp->bin_paths_len);
		tmp = tmp->next;
	}
}

path_list *create_path_node(char *full_path_env, int *st_idx)
{
	path_list *new = malloc(sizeof(path_list));
	int hold = *st_idx, len = 0, i;

	while (full_path_env[*st_idx] != ':' && full_path_env[*st_idx] != '\0')
	{
		len++;
		*st_idx += 1;
	}
	new->bin_paths_len = len;
	new->bin_paths = malloc((len + 1) * sizeof(char));
	new->next = NULL;
	for (i = 0; i < len; i++, hold++)
	{
		new->bin_paths[i] = full_path_env[hold];
	}
	new->bin_paths[i] = '\0';
	return (new);
}

void free_path_list(path_list **h)
{
	path_list *tmp;

	while (*h)
	{
		tmp = (*h)->next;
		free((*h)->bin_paths);
		free((*h));
		(*h) = tmp;
	}
	(*h) = NULL;
}

path_list *append_path_node(path_list **h, char *full_path_env, int *st_idx)
{
	path_list *new, *tmp = *h;

	new = create_path_node(full_path_env, st_idx);
	if (!(*h))
	{
		*h = new;
		return (new);
	}

	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (new);
}