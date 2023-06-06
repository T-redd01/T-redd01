#include "main.h"

void cmd_list_handle(state_of_shell *vars, size_t cmds, cmd_buf *h)
{
	char *num = _itoa(&cmds);
	size_t args_len, name_len;

	if (vars->err_prmpt)
		free(vars->err_prmpt);
	args_len = _strlen(h->args[0]);
	name_len = _strlen(vars->prog_name);
	vars->err_prmpt = malloc((cmds + 5 + args_len + name_len) * sizeof(char));
	if (!vars->err_prmpt)
	{
		perror("malloc:");
		exit(errno);
	}
	_strcpy(vars->err_prmpt, vars->prog_name);
	_strcat(vars->err_prmpt, ": ");
	_strcat(vars->err_prmpt, num);
	_strcat(vars->err_prmpt, ": ");
	_strcat(vars->err_prmpt, h->args[0]);
	free(num);
	return;
}

int eval_inp(state_of_shell *vars, size_t cmds)
{
	int path_exists, builtin_found;
	tokens *head = NULL;
	cmd_buf *start = NULL;

	head = new_list(vars->inpbuf);
	free(vars->inpbuf);
	vars->inpbuf = NULL;
	find_var(&head);
	if (!head)
		return (0);
	vars->all_cmds = create_cmd_buf(&head);
	free_tokens_list(head);

	start = vars->all_cmds;
	while (start)
	{
		if (vars->cmd)
		{
			free(vars->cmd);
			vars->cmd = NULL;
		}
		cmd_list_handle(vars, cmds, start);
		builtin_found = built_in_findr(start->args, vars);
		if (builtin_found)
		{
			start = start->n_cmd;
			continue;
		}
		path_exists = path_findr(vars, start->args);
		if (!path_exists)
			execute_cmd(vars, start->args);

		if (start->chain_symbol == '&' && errno != 0)
		{
			while (start && start->chain_symbol != ';' && start->chain_symbol != '|')
				start = start->n_cmd;
			if (start)
				start = start->n_cmd;
			continue;
		}
		if (start->chain_symbol == '|' && errno == 0)
		{
			while (start && start->chain_symbol != ';' && start->chain_symbol != '&')
				start = start->n_cmd;
			if (start)
				start = start->n_cmd;
			continue;
		}

		if (start)
			start = start->n_cmd;
	}
	free_cmd_list(vars->all_cmds);
	return 0;
}