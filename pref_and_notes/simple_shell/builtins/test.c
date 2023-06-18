#include "main.h"

int main(__attribute__((unused)) int ac, __attribute__((unused)) char **av) {
	cache mm = {NULL, NULL, NULL};
	if (ac != 1) {
		return (1);
	}
	init_environ();
	repl_loop(&mm, av[0]);
	/*int i;

	for (i = 0; i < 1124; i++)
		_putchar('r');*/
	return (0);
}

