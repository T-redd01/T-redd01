#include "main.h"

path_list *init_path_list(path_list **h)
{
	path_list *ret;
	char *full_path_env = _getenv("PATH");
	int i = 0, idx_point;

	while (full_path_env[i])
	{
		if (full_path_env[i] != ':' && full_path_env[i] != '\0')
		{
			ret = append_path_node(h, full_path_env, &i);
			i--;
		}
		i++;
	}
	return (ret);
}

int path_findr(state_of_shell *vars)
{
	int i = 0, file_found;
	char *test_path;
	struct stat statbuf;
	path_list *tmp;

	if (!vars->path_env)
	{
		init_path_list(&(vars->path_env));
	}

	tmp = vars->path_env;
	while (tmp)
	{
		test_path = malloc((tmp->bin_paths_len + _strlen(vars->args[0]) + 2));
		_strcpy(test_path, tmp->bin_paths);
		_strcat(test_path, "/");
		_strcat(test_path, vars->args[0]);
		file_found = stat(test_path, &statbuf);
		if (file_found == 0)
		{
			vars->cmd = test_path;
			return (0);
		}
		free(test_path);
		tmp = tmp->next;
	}
	return (1);
}