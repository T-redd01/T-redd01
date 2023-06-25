#include "main.h"

int builtin_findr(cache *mm, char **vect) {
	int i;

	builtins funcs[] = {
		{"exit", shell_exit},
		{"alias", _alias},
		{"cd", _change_WD},
		{"setenv", call_setenv},
		{"unsetenv", call_unsetenv},
		{"env", print_env},
		{NULL, NULL},
	};

	for (i = 0; funcs[i].name; i++) {
		if ((my_strcmp(vect[0], funcs[i].name))) {
			funcs[i].p(mm, vect);
			return (1);
		}
	}
	return (0);
}
