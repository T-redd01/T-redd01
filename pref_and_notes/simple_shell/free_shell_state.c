#include "main.h"

void free_state_args(char **args)
{
	unsigned int i;

	for (i = 0; args[i]; i++)
	{
		free(args[i]);
	}
	free(args);
	args = NULL;
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

void free_everthing(state_of_shell *vars)
{
	if (vars->args)
		free_state_args(vars->args);

	if (vars->cmd)
	{
		free(vars->cmd);
		vars->cmd = NULL;
	}

	if (vars->inpbuf)
	{
		free(vars->inpbuf);
		vars->inpbuf = NULL;
	}

	if (vars->path_env)
		free_path_list(&(vars->path_env));
}