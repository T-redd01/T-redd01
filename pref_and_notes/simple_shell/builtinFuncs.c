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
	char *to_cd;

	if (vars->args[1] == NULL)
		to_cd = _getenv("HOME"); /* oldpwd = pwd , pwd = /home/otto */
	else if (vars->args[1][0] == '-' && vars->args[1][1] == '\0')
	{
		to_cd = _getenv("OLDPWD"); /* oldpwd = pwd, pwd = oldpwd */
		_puts(to_cd, 1);
		_puts("\n", 1);
	}
	else
		to_cd = vars->args[1]; /* oldpwd = pwd , pwd = newpwd */

	if (chdir(to_cd) == -1)
	{
		_puts(vars->err_prmpt, 2);
		_puts(err_msg, 2);
		_puts(vars->args[1], 2);
		_puts("\n", 2);
		return (1);
	}
	change_dir_env();
	return (1);
}

int call_setenv(state_of_shell *vars)
{
	if ((err_setenv(vars->args)))
		return (1);

	return ((_setenv(vars->args[1], vars->args[2])));
}

int print_env(__attribute__((unused)) state_of_shell *vars)
{
	size_t i;

	for (i = 0; environ[i]; i++)
	{
		_puts(environ[i], 1);
		_puts("\n", 1);
	}
	return (1);
}

int _unsetenv(state_of_shell *vars)
{
	int i = 0;
	char **holder;

	while (vars->args[i])
	{
		i++;
		if (i > 2)
		{
			_puts("Usage: unsetenv [NAME]\n", 2);
			return (1);
		}
	}

	holder = malloc(matrix_counter(environ) * sizeof(char *));
	for (i =)
}