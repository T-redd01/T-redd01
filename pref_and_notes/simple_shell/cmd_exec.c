#include "main.h"

int execute_cmd(state_of_shell *vars, char **vect)
{
	pid_t child_proc;
	int wstatus;

	child_proc = fork();
	if (child_proc == 0)
	{
		execve(vars->cmd, vect, environ);
	}
	else
	{
		wait(&wstatus);
		errno = WEXITSTATUS(wstatus);
	}
	return (0);
}