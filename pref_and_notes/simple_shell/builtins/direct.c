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
		_puts(curr, 1);
		_puts("\n", 1);
		return;
	}

	if ((chdir(new)) == -1) {
		perror("reverse_dir: oldpwd");
		free(new);
		return;
	}
	_puts(new, 1);
	_puts("\n", 1);
	_setenv("PWD", new);
	_setenv("OLDPWD", curr);
	free(new);
}

void cd_err_msg(char *tok) {
	_puts("Cant't cd to: ", 1);
	_puts(tok, 1);
	_puts("\n", 1);
}

void _change_WD(char **vect) {
        int ch_ret = 0;
        char *path = NULL, *curr = NULL;

        curr = _getCWD();
		if (!curr)
			return;

		if (!vect[1]) {
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

		if ((my_strcmp(vect[1], "-"))) {
			reverse_dir(curr);
			free(curr);
			return;
		}

		ch_ret = chdir(vect[1]);
		if (ch_ret == -1) {
			cd_err_msg(vect[1]);
			free(curr);
			return;
		}
		update_oldpwd(curr);
		free(curr);
}

