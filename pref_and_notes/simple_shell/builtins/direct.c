#include "main.h"
char *_getCWD(size_t num) {
    size_t i;
    char *buf = NULL;

    buf = malloc(num * sizeof(char));
    if (!buf) {
        perror("my_get: buf");
        return (NULL);
    }   

    getcwd(buf, num);
    if (errno == 34) {
        errno = 0;
        for (i = 0; i < (num - 1); i++)
            buf[i] = 'r';
        buf[i] = '\0';
        free(buf);
        return (_getCWD(num * 2));
    }   
    return (buf);
}

void update_oldpwd(char *curr) {
	char *new = _getCWD(1);

	if (!curr || !new)
		return;

	_setenv("OLDPWD", curr);
	_setenv("PWD", new);
	free(new);
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
	_puts("Cant't cd to: ", 2);
	_puts(tok, 2);
	_puts("\n", 2);
}

void _change_WD(char **vect) {
        int ch_ret = 0;
        char *path = NULL, *curr = NULL;

        curr = _getCWD(1);
		if (!curr)
			return;

		if (!vect[1]) {
			path = _strdup(_getenv("HOME"));
			if (!path) {
				printf("before free curr\n");
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

