#include "main.h"

path_list *init_path_list(path_list **h)
{
	char *full_path_env = _getenv("PATH");
	int i = 0, idx_point;

	while (full_path_env[i])
	{
		if (full_path_env[i] != ':' && full_path_env[i] != '\0')
		{
			append_path_node(h, full_path_env, &i);
			i--;
		}
		i++;
	}
	printf("%d\n", i);

	return (NULL);
}

int path_findr(state_of_shell *vars)
{
	if (!vars->path_env)
	{
		init_path_list(&(vars->path_env));
	}
	return (0);
}