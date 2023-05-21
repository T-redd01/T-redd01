#include "main.h"

int exit_shell(state_of_shell *vars)
{
	ssize_t _status;
	char *err_msg = ": Illegal number: ";
	char *ex_arg = vars->args[1];

	if (ex_arg)
		_status = _atoi(ex_arg);
	else
		_status = (ssize_t)errno;

	if (_status < 0)
	{
		_puts(vars->err_prmpt, 2);
		_puts(err_msg, 2);
		_puts(vars->args[1], 2);
		_puts("\n", 2);
		errno = 2;
		return (-1);
	}
	free_all(vars);
	free_repl(vars);
	exit(_status);
}

int change_directory(state_of_shell *vars)
{
	char *err_msg = ": can't cd to ";
	if (chdir(vars->args[1]) == -1)
	{
		_puts(vars->err_prmpt, 2);
		_puts(err_msg, 2);
		_puts(vars->args[1], 2);
		_puts("\n", 2);
	}
	return (1);
}