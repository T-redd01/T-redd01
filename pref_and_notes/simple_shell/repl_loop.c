#include "main.h"

int sighit = 0;

void sighandler(int sig)
{
	sighit = 1;
	write(STDOUT_FILENO, "\n$ ", 3);
}

ssize_t read_inp(char **input)
{
	size_t n = 0;
	ssize_t rline;
	if (isatty(STDIN_FILENO) && !sighit)
	{
		write(STDOUT_FILENO, "$ ", 2);
	}
	rline = getline(input, &n, stdin);
	sighit = 0;
	return (rline);
}

void cmd_list_handle(state_of_shell *vars, int cmds)
{
	char *num = _itoa(&cmds);
	size_t args_len, name_len;

	args_len = _strlen(vars->args[0]);
	name_len = _strlen(vars->prog_name);
	vars->err_prmpt = malloc((cmds + 5 + args_len + name_len) * sizeof(char));
	_strcpy(vars->err_prmpt, vars->prog_name);
	_strcat(vars->err_prmpt, ": ");
	_strcat(vars->err_prmpt, num);
	_strcat(vars->err_prmpt, ": ");
	_strcat(vars->err_prmpt, vars->args[0]);
	free(num);
}

void repl_loop(state_of_shell *vars)
{
	ssize_t retval;
	int path_exists, cmds = 0;

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
			exit(vars->exit_status);
		}

		if (retval == 1 && *(vars->inpbuf) == '\n')
		{
			free(vars->inpbuf);
			continue;
		}

		input_parser(vars);
		cmd_list_handle(vars, cmds);
		path_exists = path_findr(vars);
		if (!path_exists)
		{
			execute_cmd(vars);
		}
		free_repl(vars);
	}
}