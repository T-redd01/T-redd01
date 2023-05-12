#include "main.h"

int main(int ac, char **av)
{
	state_of_shell vars = {.prog_name = NULL, .inpbuf = NULL, .args = NULL, .cmd = NULL, .path_env = NULL};

	vars.prog_name = av[0];
	repl_loop(&vars);
	return (0);
}