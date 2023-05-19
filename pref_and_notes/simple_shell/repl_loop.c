#include "main.h"

int sighit = 0;

void sighandler(__attribute__((unused)) int sig)
{
	sighit = 1;
	errno = 130;
	_puts("\n$ ", 1);
}

ssize_t read_inp(char **input)
{
	size_t n = 0;
	ssize_t rline;

	if (isatty(STDIN_FILENO) && !sighit)
	{
		_puts("$ ", 1);
	}
	rline = getline(input, &n, stdin);
	sighit = 0;
	return (rline);
}

void repl_loop(state_of_shell *vars)
{
	ssize_t retval;
	size_t cmds = 0;

	signal(SIGINT, &sighandler);
	while (1)
	{
		cmds++;
		retval = read_inp(&(vars->inpbuf));
		if (retval == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free_all(vars);
			exit(errno);
		}

		if (retval == 1 && *(vars->inpbuf) == '\n')
		{
			free(vars->inpbuf);
			continue;
		}

		eval_inp(vars, cmds);
		free_repl(vars);
	}
}