#include "main.h"

int built_in_findr(state_of_shell *vars)
{
	int i, match;

	builtin my_cmds[] = {
		{"exit", exit_shell},
		{"env", print_env},
		{"cd", change_directory},
		{"setenv", _setenv},
		{"\0", NULL},
	};

	for (i = 0; my_cmds[i].builtin_name[0]; i++)
	{
		match = _strcmp(my_cmds[i].builtin_name, vars->args[0]);
		if (match)
		{
			return (my_cmds[i].func_ptr(vars));
		}
	}
	return (0);
}