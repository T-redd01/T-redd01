#include "main.h"

void free_environ(void)
{
	size_t i;

	for (i = 0; environ[i]; i++)
		free(environ[i]);
	free(environ);
}

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

	if (environ)
		free_environ();

	if (vars->path_env)
	{
		free_path_list(&(vars->path_env));
	}
}