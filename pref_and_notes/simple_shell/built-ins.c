#include "main.h"

int built_in_findr(state_of_shell *vars)
{
	int i, match;

	builtin my_cmds[] = {
		{"exit"},
		{"env"},
		{"cd"},
		{"\0"},
	};

	for (i = 0; my_cmds[i].builtin_name[0]; i++)
	{
		match = _strcmp(my_cmds[i].builtin_name, vars->args[0]);
		/*if (match)
		{
		}*/
	}
	return (0);
}