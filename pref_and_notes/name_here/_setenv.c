#include "main.h"

char *new_env_var(char *name, char *val) {
	size_t i, j = 0, name_len = 0, val_len = 0;
	char *new = NULL;

	if (!name || !val)
		return (NULL);

	while (name[name_len])
		name_len++;
	while (val[val_len])
		val_len++;

	new = malloc((name_len + val_len + 2) * sizeof(char));
	if (!new) {
		perror("new_env_var: new");
		return (NULL);
	}

	for (i = 0; name[i]; i++)
		new[j++] = name[i];
	new[j++] = '=';
	for (i = 0; val[i]; i++)
		new[j++] = val[i];
	new[j] = '\0';
	return (new);
}

void replace_env(char *name, char *val) {
	size_t i;
	char *var = NULL;

	var = new_env_var(name, val);
	if (!var) {
		perror("replace_env: var");
		return;
	}
	for (i = 0; environ[i]; i++) {
		if ((key_cmp(environ[i], name))) {
			free(environ[i]);
			environ[i] = var;
			continue;
		}
	}
}

void _setenv(char *name, char *val) {
	size_t i, args = matrix_count(environ);
	char **holder = NULL, *var = NULL;

	if (!name || !val)
		return;

	if ((_getenv(name))) {
		replace_env(name, val);
		return;
	}
	holder = malloc((args + 2) * sizeof(char *));
	if (!holder) {
		perror("_setenv: holder");
		return;
	}
	var = new_env_var(name, val);
	if (!var) {
		perror("_setenv: var");
		free(holder);
		return;
	}
	for (i = 0; environ[i]; i++)
		holder[i] = _strdup(environ[i]);
	holder[i++] = var;
	holder[i] = NULL;

	free_matrix(environ);
	environ = malloc((args + 2) * sizeof(char *));
	if (!environ) {
		perror("_setenv: environ");
		return;
	}
	for (i = 0; holder[i]; i++)
		environ[i] = holder[i];
	environ[i] = NULL;
	free(holder);
}

void call_setenv(__attribute__((unused)) cache *mm, char **vect) {
	int args = 0;

	errno = 0;
	while (vect[args]) {
		if (args == 4)
			break;
		args++;
	}

	if (args != 3) {
		errno = 1;
		_puts("Usage: setenv [VARIABLE NAME] [VARIABLE VALUE]\n", 2);
		return;
	}

	_setenv(vect[1], vect[2]);
}

