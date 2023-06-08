#include "main.h"

int exit_shell(char **vect, state_of_shell *vars)
{
	ssize_t _status;
	char *err_msg = ": Illegal number: ";
	char *ex_arg = vect[1];

	if (ex_arg)
		_status = _atoi(ex_arg);
	else
		_status = (ssize_t)errno;

	if (_status < 0)
	{
		_puts(vars->err_prmpt, 2);
		_puts(err_msg, 2);
		_puts(vect[1], 2);
		_puts("\n", 2);
		errno = 2;
		return (-1);
	}
	free_all(vars);
	free_repl(vars);
	free_cmd_list(vars->all_cmds);
	exit(_status);
}

int change_directory(char **vect, state_of_shell *vars)
{
	char *err_msg = ": can't cd to ";
	char *to_cd = NULL, buf[2048];

	if (vect[1] == NULL)
		to_cd = _getenv("HOME"); /* oldpwd = pwd , pwd = /home/otto */
	else if (vect[1][0] == '-' && vect[1][1] == '\0')
	{
		to_cd = _getenv("OLDPWD"); /* oldpwd = pwd, pwd = oldpwd */
		if (!to_cd)
			to_cd = getcwd(buf, 2048);
		_puts(to_cd, 1);
		_puts("\n", 1);
	}
	else
		to_cd = vect[1]; /* oldpwd = pwd , pwd = newpwd */

	if (chdir(to_cd) == -1)
	{
		_puts(vars->err_prmpt, 2);
		_puts(err_msg, 2);
		_puts(vect[1], 2);
		_puts("\n", 2);
		return (1);
	}
	change_dir_env();
	return (1);
}

int call_setenv(char **vect, __attribute__((unused)) state_of_shell *vars)
{
	if ((err_setenv(vect)))
		return (1);

	return ((_setenv(vect[1], vect[2])));
}

int print_env(__attribute__((unused)) char **vect, __attribute__((unused)) state_of_shell *vars)
{
	size_t i;

	for (i = 0; environ[i]; i++)
	{
		_puts(environ[i], 1);
		_puts("\n", 1);
	}
	return (1);
}

int _unsetenv(char **vect, __attribute__((unused)) state_of_shell *vars)
{
	int i = 0, j = 0, flag = 0;
	char **holder = NULL;

	while (vect[i])
	{
		i++;
		if (i > 2)
		{
			_puts("Usage: unsetenv [NAME]\n", 2);
			return (1);
		}
	}
	if (i < 2)
	{
		_puts("Usage: unsetenv [NAME]\n", 2);
		return (1);
	}

	holder = malloc((matrix_counter(environ) + 1) * sizeof(char *));
	for (i = 0; environ[i]; i++, j++)
	{
		if ((_strcmp_setenv(environ[i], vect[1])))
		{
			flag = 1;
			continue;
		}
		holder[j] = _strdup(environ[i]);
	}
	holder[j] = NULL;

	if (!flag)
	{
		_puts("Variable not found\n", 2);
		free_state_args(holder);
		return (1);
	}

	free_state_args(environ);
	environ = malloc((matrix_counter(holder) + 1) * sizeof(char *));
	for (i = 0; holder[i]; i++)
	{
		environ[i] = _strdup(holder[i]);
		free(holder[i]);
	}
	environ[i] = NULL;
	free(holder);
	return (1);
}
