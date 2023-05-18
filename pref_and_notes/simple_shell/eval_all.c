#include "main.h"

void cmd_list_handle(state_of_shell *vars, size_t cmds)
{
	char *num = _itoa(&cmds);
	size_t args_len, name_len;

	if (!vars->err_prmpt)
		free(vars->err_prmpt);
	args_len = _strlen(vars->args[0]);
	name_len = _strlen(vars->prog_name);
	if (vars->err_prmpt)
		printf("not null: %s\n", vars->err_prmpt);
	vars->err_prmpt = malloc((cmds + 5 + args_len + name_len) * sizeof(char));
	_strcpy(vars->err_prmpt, vars->prog_name);
	printf("err prmpt1: %s\n", vars->err_prmpt);
	_strcat(vars->err_prmpt, ": ");
	printf("err prmpt2: %s\n", vars->err_prmpt);
	_strcat(vars->err_prmpt, num);
	printf("err prmpt3: %s\n", vars->err_prmpt);
	_strcat(vars->err_prmpt, ": ");
	printf("err prmpt4: %s\n", vars->err_prmpt);
	_strcat(vars->err_prmpt, vars->args[0]);
	printf("err prmpt5: %s\n", vars->err_prmpt);
	free(num);
}

int eval_inp(state_of_shell *vars, size_t cmds)
{
	int path_exists;

	input_parser(vars);
	cmd_list_handle(vars, cmds);
	path_exists = path_findr(vars);
	if (!path_exists)
		execute_cmd(vars);
	return (0);
}