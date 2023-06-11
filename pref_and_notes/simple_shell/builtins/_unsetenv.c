#include "main.h"

void _unsetenv(char *name) {
        int i, j = 0, args = matrix_count(environ);
        char **holder = NULL;

        if (!name)
                return;

        holder = malloc(args * sizeof(char *));
        if (!holder) {
                perror("_unsetenv: holder");
                return;
        }
        for (i = 0; environ[i]; i++) {
                if ((key_cmp(environ[i], name)))
                        continue;
                holder[j++] = _strdup(environ[i]);
        }
        holder[j] = NULL;

        free_matrix(environ);
        environ = malloc(args * sizeof(char *));
        if (!environ) {
                perror("_unsetenv: environ");
                free_matrix(holder);
                return;
        }
        for (i = 0; holder[i]; i++) {
                environ[i] = holder[i];
        }
        environ[i] = NULL;
        free(holder);
}

void call_unsetenv(char **vect) {
	int args = 0;

	while (vect[args]) {
		if (args == 3)
			break;
		args++;
	}

	if (args != 2) {
		_puts("Usage: unsetenv [VARIABLE NAME]\n", 2);
		return;
	}

	if (!(_getenv(vect[1]))) {
		_puts("Variable not found\n", 2);
		return;
	}

	_unsetenv(vect[1]);
}

