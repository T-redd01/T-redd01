#include "main.h"

void init_environ(void)
{
	int i;
	char **holder;

	holder = malloc((matrix_counter(environ) + 1) * sizeof(char *));
	for (i = 0; environ[i]; i++)
		holder[i] = _strdup(environ[i]);
	holder[i] = NULL;

	environ = malloc((matrix_counter(holder) + 1) * sizeof(char *));
	for (i = 0; holder[i]; i++)
		environ[i] = _strdup(holder[i]);
	environ[i] = NULL;

	for (i = 0; holder[i]; i++)
		free(holder[i]);
	free(holder);
}

int main(__attribute__((unused)) int ac, char **av)
{
	state_of_shell vars = {NULL, NULL, NULL, NULL, NULL, NULL};

	vars.prog_name = av[0];
	init_environ();
	repl_loop(&vars);
	return (0);
}