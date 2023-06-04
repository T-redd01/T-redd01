#include "main.h"
/*
int num_of_words(char *s)
{
	int words = 0, i = 0;

	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\n')
		{
			if (s[i - 1] == ' ' && s[i] == '#')
				break;
			words++;
			while (s[i] != ' ' && s[i] != '\0' && s[i] != '\n')
				i++;
			i--;
		}
		i++;
	}
	return (words);
}

void sep_args(state_of_shell *vars, int word_idx, int arg_index)
{
	int i = 0;

	while (vars->inpbuf[word_idx] != ' ' && vars->inpbuf[word_idx] != '\n')
	{
		vars->args[arg_index][i] = vars->inpbuf[word_idx];
		i++;
		word_idx++;
	}
	vars->args[arg_index][i] = '\0';
}

void exp_parser(state_of_shell *vars)
{
	int i, j, hold_idx = 0, k;
	char **cp_args = vars->args;
	char holder[4096], *tmp = NULL;

	for (i = 0; cp_args[i]; i++)
	{
		hold_idx = 0;
		for (j = 0; cp_args[i][j]; j++)
		{
			if (cp_args[i][j] == '$')
				tmp = var_exp(vars, i, &j);
			else
				holder[hold_idx++] = vars->args[i][j];

			if (cp_args[i][j] == '\0')
				j--;

			if (tmp)
			{
				for (k = 0; tmp[k]; k++, hold_idx++)
					holder[hold_idx] = tmp[k];
				holder[hold_idx] = '\0';
				free(tmp);
				tmp = NULL;
			}
		}
		free(vars->args[i]);
		holder[hold_idx] = '\0';
		vars->args[i] = _strdup(holder);
	}
}

void input_parser(state_of_shell *vars)
{
	char *tmp = vars->inpbuf;
	int i = 0, idx_point = 0, args_idx = 0, words, word_len;

	words = num_of_words(tmp);
	vars->args = malloc((words + 1) * sizeof(char *));
	while (tmp[i])
	{
		if (tmp[i] != ' ' && tmp[i] != '\n')
		{
			if (tmp[i - 1] == ' ' && tmp[i] == '#')
				break;
			word_len = 0;
			idx_point = i;
			while (tmp[i] != ' ' && tmp[i] != '\0' && tmp[i] != '\n')
			{
				word_len++;
				i++;
			}
			i--;
			vars->args[args_idx] = malloc((word_len + 1) * sizeof(char));
			sep_args(vars, idx_point, args_idx);
			args_idx++;
		}
		i++;
	}
	vars->args[args_idx] = NULL;
	exp_parser(vars);
}
*/