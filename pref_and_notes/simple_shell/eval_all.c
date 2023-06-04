#include "main.h"

void cmd_list_handle(state_of_shell *vars, size_t cmds, cmd_buf *h)
{
	char *num = _itoa(&cmds);
	size_t args_len, name_len;

	if (!vars->err_prmpt)
		free(vars->err_prmpt);
	args_len = _strlen(h->args[0]);
	name_len = _strlen(vars->prog_name);
	vars->err_prmpt = malloc((cmds + 5 + args_len + name_len) * sizeof(char));
	_strcpy(vars->err_prmpt, vars->prog_name);
	_strcat(vars->err_prmpt, ": ");
	_strcat(vars->err_prmpt, num);
	_strcat(vars->err_prmpt, ": ");
	_strcat(vars->err_prmpt, h->args[0]);

	free(num);
	return;
}

int eval_inp(state_of_shell *vars, __attribute__((unused)) size_t cmds)
{
	int path_exists, builtin_found;
	tokens *head = NULL;
	cmd_buf *start = vars->all_cmds;

	head = new_list(vars->inpbuf);
	free(vars->inpbuf);
	vars->inpbuf = NULL;
	find_var(&head);
	if (!head)
		return (0);
	start = create_cmd_buf(&head);
	free_tokens_list(head);

	while (start)
	{
		cmd_list_handle(vars, cmds, start);

		builtin_found = built_in_findr(start->args, vars->err_prmpt);
		if (builtin_found)
			continue;

		path_exists = path_findr(vars, start->args);
		if (!path_exists)
			execute_cmd(vars, start->args);
		start = start->n_cmd;
	}

	free_cmd_list(vars->all_cmds);
	return (0);
}