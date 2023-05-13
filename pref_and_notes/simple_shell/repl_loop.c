#include "main.h"

void sighandler(int sig)
{
	write(STDOUT_FILENO, "\n$ ", 3);
}

ssize_t read_inp(char **input)
{
	size_t n = 0;
	ssize_t rline;
	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "$ ", 2);
	}
	rline = getline(input, &n, stdin);
	return (rline);
}

void repl_loop(state_of_shell *vars)
{
	ssize_t retval;
	int path_exists;

	signal(SIGINT, &sighandler);
	while (1)
	{
		retval = read_inp(&(vars->inpbuf));
		if (retval == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free_everthing(vars);
			exit(0);
		}

		if (retval == 1 && *(vars->inpbuf) == '\n')
		{
			free(vars->inpbuf);
			continue;
		}
		input_parser(vars);
		path_exists = path_findr(vars);
		if (!path_exists)
		{
			execute_cmd(vars);
			free(vars->cmd);
			vars->cmd = NULL;
		}
		free(vars->inpbuf);
	}
}