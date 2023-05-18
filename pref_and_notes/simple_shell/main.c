#include "main.h"

int main(__attribute__((unused)) int ac, char **av)
{
	state_of_shell vars = {NULL, NULL, NULL, NULL, NULL, NULL};

	vars.prog_name = av[0];
	repl_loop(&vars);
	return (0);
}