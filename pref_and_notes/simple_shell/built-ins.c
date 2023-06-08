#include "main.h"

void change_dir_env(void)
{
	char *tmp = _strdup(_getenv("PWD"));
	char curr[2048];

	if (!tmp)
	{
		tmp = getcwd(curr, 2048);
		printf("tmp: %s\n", tmp);
	}
	_setenv("OLDPWD", tmp);
	_setenv("PWD", getcwd(curr, 2048));
	free(tmp);
}

int built_in_findr(char **vect, state_of_shell *vars)
{
	int i, match = 0;

	builtin my_cmds[] = {
		{"exit", exit_shell},
		{"env", print_env},
		{"cd", change_directory},
		{"setenv", call_setenv},
		{"unsetenv", _unsetenv},
		{"\0", NULL},
	};

	for (i = 0; my_cmds[i].builtin_name[0]; i++)
	{
		match = _strcmp(my_cmds[i].builtin_name, vect[0]);
		if (match)
		{
			return (my_cmds[i].func_ptr(vect, vars));
		}
	}
	return (0);
}