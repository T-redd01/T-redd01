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

int _setenv(state_of_shell *vars)
{
	int i, flag = 0, idx = -1;
	char **holder;

	if ((err_setenv(vars->args)))
		return (1);

	holder = malloc((matrix_counter(environ) + 1) * sizeof(char *));
	for (i = 0; environ[i]; i++)
	{
		if ((flag = _strcmp_setenv(environ[i], vars->args[1])))
			idx = i;
		holder[i] = _strdup(environ[i]);
	}
	holder[i] = NULL;

	free_environ();
	if (idx != -1)
		environ = malloc((matrix_counter(holder) + 1) * sizeof(char *));
	else
		environ = malloc((matrix_counter(holder) + 2) * sizeof(char *));
	for (i = 0; holder[i]; i++)
	{
		if (i == idx)
		{
			environ[i] = add_env(vars->args[1], vars->args[2]);
			continue;
		}
		environ[i] = _strdup(holder[i]);
	}
	if (idx == -1)
		environ[i++] = add_env(vars->args[1], vars->args[2]);
	environ[i] = NULL;

	for (i = 0; holder[i]; i++)
		free(holder[i]);
	free(holder);
	return (1);
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