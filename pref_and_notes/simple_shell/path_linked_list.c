#include "main.h"

path_list *create_path_node(char *full_path_env, int *st_idx)
{
	path_list *new = malloc(sizeof(path_list));
	int hold = *st_idx, len = 0;

	while (full_path_env[*st_idx] != ':' && full_path_env[*st_idx] != '\0')
	{
		len++;
		printf("%c", full_path_env[*st_idx]);
		*st_idx += 1;
	}
	printf("len: %d\n", len);
	free(new);
	return (NULL);
}

path_list *append_path_node(path_list **h, char *full_path_env, int *st_idx)
{
	path_list *new;

	new = create_path_node(full_path_env, st_idx);
	return (NULL);
}