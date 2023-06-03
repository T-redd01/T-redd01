#include "main.h"

void cmd_list_handle(state_of_shell *vars, size_t cmds)
{
	char *num = _itoa(&cmds);
	size_t args_len, name_len;

	if (!vars->err_prmpt)
		free(vars->err_prmpt);
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

int eval_inp(state_of_shell *vars, __attribute__((unused)) size_t cmds)
{
	/*int path_exists, builtin_found;*/
	tokens *head = NULL;
	cmd_buf *start = NULL;

	printf("Input: %s\n", vars->inpbuf);
	head = new_list(vars->inpbuf);
	free(vars->inpbuf);
	vars->inpbuf = NULL;
	find_var(&head);
	printf("\nTokens:\n");
	print_tokens_list(head);
	start = create_cmd_buf(&head);
	printf("\ncmds:\n");
	print_cmd_list(start);
	free_tokens_list(head);
	free_cmd_list(start);
	/*cmd_list_handle(vars, cmds);

	builtin_found = built_in_findr(vars);
	if (builtin_found)
		return (0);

	path_exists = path_findr(vars);
	if (!path_exists)
		execute_cmd(vars);*/
	return (0);
}