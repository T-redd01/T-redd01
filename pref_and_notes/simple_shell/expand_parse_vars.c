#include "main.h"

#define varInd vars->args[arg_idx][*exp_idx]

char *var_exp(state_of_shell *vars, int arg_idx, int *exp_idx)
{
	size_t num, i = 0;
	char *exp, env_var[2048];

	*exp_idx += 1;
	if (varInd == '?')
	{
		num = errno;
		exp = _itoa(&num);
		return (exp);
	}
	else if (varInd == '$')
	{
		num = getpid();
		exp = _itoa(&num);
		return (exp);
	}
	else if ((varInd >= 65 && varInd <= 90) || (varInd >= 97 && varInd <= 122)) /* A:65 Z:90 a:97 z:122 */
	{
		while (vars->args[arg_idx][*exp_idx])
		{
			env_var[i++] = vars->args[arg_idx][*exp_idx];
			*exp_idx += 1;
		}
		env_var[i] = '\0';
		exp = _strdup(_getenv(env_var));
		return (exp);
	}
	else
	{
		exp = malloc(2);
		exp[0] = '$';
		exp[1] = '\0';
		*exp_idx -= 1;
		return (exp);
	}
	return (NULL);
}