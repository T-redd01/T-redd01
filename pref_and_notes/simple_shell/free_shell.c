#include "main.h"

void free_all(state_of_shell *vars)
{
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
	{
		free_path_list(&(vars->path_env));
	}
}