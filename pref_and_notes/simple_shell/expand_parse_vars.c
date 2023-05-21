#include "main.h"

int var_exp(char **holder, state_of_shell *vars, int arg_idx, int *exp_idx)
{
	size_t num = errno;
	char *exp, *some;

	*exp_idx += 1;
	if (vars->args[arg_idx][*exp_idx] == '?')
	{
		if (*holder == NULL)
		{
			*holder = _itoa(&num);
		}
		else
		{
			exp = _itoa(&num);
			some = malloc(_strlen(exp) + _strlen(*holder) + 1);
			_strcpy(some, *holder);
			_strcat(some, exp);
			free(*holder);
			*holder = malloc((_strlen(some) + 1));
			_strcpy(*holder, some);
		}
		/*free(exp);*/
	}
	return (1);
}