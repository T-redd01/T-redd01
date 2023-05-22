#include "main.h"

void free_state_args(char **args)
{
	unsigned int i;

	for (i = 0; args[i]; i++)
	{
		free(args[i]);
	}
	free(args);
}

void free_repl(state_of_shell *vars)
{
	if (vars->args)
	{
		free_state_args(vars->args);
		vars->args = NULL;
	}
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

	if (vars->err_prmpt)
	{
		free(vars->err_prmpt);
		vars->err_prmpt = NULL;
	}
}