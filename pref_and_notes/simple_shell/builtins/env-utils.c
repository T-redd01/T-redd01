#include "main.h"

void init_environ(void) {
	size_t i, args = matrix_count(environ);
	char **holder = NULL;

	holder = malloc((args + 1) * sizeof(char *));
	if (holder == NULL) {
		perror("init_environ: holder");
		return;
	}
	for (i = 0; environ[i]; i++)
		holder[i] = _strdup(environ[i]);
	holder[i] = NULL;

	environ = malloc((args + 1) * sizeof(char *));
	for (i = 0; holder[i]; i++)
		environ[i] = holder[i];
	environ[i] = NULL;
	free(holder);
}

char *_getenv(char *name) {
        int i;
        char *var = NULL;

        if (!name)
                return (NULL);
        for (i = 0; environ[i]; i++) {
                if ((key_cmp(environ[i], name))) {
                        var = environ[i];
                        while (*var != '=')
                                var++;
                        return (++var);
                }
        }
        return (NULL);
}

int key_cmp(char *key, char *name) {
    int i;

	if (!key || !name)
		return (0);
	for (i = 0; name[i] && key[i] != '='; i++) {
		if (key[i] != name[i])
			return (0);
	}
	if (key[i] == '=' && name[i] == '\0')
		return (1);
	return (0);
}

