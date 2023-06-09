#include "main.h"

char *_getCWD(void) {
	char dest[4096], *path = NULL;

	getcwd(dest, 4096);
	if (errno == 34) {
		errno = 0;
		getcwd(dest, 8192);
	}
	path = _strdup(dest);    
	return (path);
}

void update_oldpwd(char *curr) {
	char *new = _getCWD();

	if (!curr || !new)
		return;

	_setenv("OLDPWD", curr);
	_setenv("PWD", new);
}

void reverse_dir(char *curr){
	char *new = NULL;

	if (!curr)
		return;

	new = _strdup(_getenv("OLDPWD"));
	if (!new) {
		printf("%s\n", curr);
		return;
	}

	if ((chdir(new)) == -1) {
		perror("reverse_dir: oldpwd");
		free(new);
		return;
	}
	printf("%s\n", new);
	_setenv("PWD", new);
	_setenv("OLDPWD", curr);
	free(new);
}

void _change_WD(char *dest) {
        int ch_ret = 0;
        char *path = NULL, *curr = NULL;

        curr = _getCWD();
		if (!curr)
			return;

		if (!dest) {
			path = _strdup(_getenv("HOME"));
			if (!path) {
				free(curr);
				return;
			}
			ch_ret = chdir(path);
			if (ch_ret == -1) {
				perror("_change_WD: home");
				free(curr);
				free(path);
			}
			free(path);
			update_oldpwd(curr);
			free(curr);
			return;
		}

		if ((my_strcmp(dest, "-"))) {
			reverse_dir(curr);
			free(curr);
			return;
		}

		ch_ret = chdir(dest);
		if (ch_ret == -1) {
			printf("Can't cd to: %s\n", dest);
			free(curr);
			return;
		}
		update_oldpwd(curr);
		free(curr);
}

