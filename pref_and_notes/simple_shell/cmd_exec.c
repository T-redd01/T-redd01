#include "main.h"

int execute_cmd(state_of_shell *vars)
{
	pid_t child_proc;

	child_proc = fork();
	if (child_proc == 0)
	{
		execve(vars->cmd, vars->args, environ);
	}
	else
	{
		wait(NULL);
	}
	return (0);
}