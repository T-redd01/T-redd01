#include "main.h"

void print_exit_err(char *num) {
	if (!num)
		return;

	_puts("hsh: 1: exit: Illegal number: ", 2);
	_puts(num, 2);
	_puts("\n", 2);
}

void shell_exit(char **vect) {
	int i, status = 0;

	if (!vect[1]) {
		/* free stuff here */
		exit(errno);
	}

	for (i = 0; vect[1][i]; i++) {
		if (vect[1][i] < 48 || vect[1][i] > 57) {
			print_exit_err(vect[1]);
			return;
		}
		status = (status * 10) + (vect[1][i] - 48);
	}

	/* free stuff here */
	exit(status);
}

