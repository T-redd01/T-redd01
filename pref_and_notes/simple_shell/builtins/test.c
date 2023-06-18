#include "main.h"

/* extra funcs */
void exec_func(char **vect) {
	pid_t cpid;
	int wstatus;

	cpid = fork();
	if (cpid == 0) {
		if ((execve(vect[0], vect, environ)) == -1) {
			perror("exec_func: execve");
			return;
		}
	} else {
		wait(&wstatus);
		errno = WEXITSTATUS(wstatus);
	}
}
/*
char *call_no(char *prog_name, size_t call) {
	size_t i, j = 0, len = 0;
	char *shell_call = NULL, *num = NULL;

	if (!prog_name)
		return (NULL);

	num = _itoa(call);
	len = _strlen(prog_name) + _strlen(num);
	shell_call = malloc((len + 5) * sizeof(char));
	if (!shell_call) {
		perror("call_no: shell_call");
		free(num);
		return (NULL);
	}

	for (i = 0; prog_name[i]; i++)
		shell_call[j++] = prog_name[i];
	shell_call[j++] = ':';
	shell_call[j++] = ' ';
	for (i = 0; num[i]; i++)
		shell_call[j++] = num[i];
	shell_call[j++] = ':';
	shell_call[j++] = ' ';
	shell_call[j] = '\0';
	free(num);
	return (shell_call);
}

char *_realloc(char *old, size_t new_size) {
	char *new = NULL;

	new = malloc(new_size);
	if (!new) {
		perror("_realloc: new");
		return (NULL);
	}

	_strcpy(new, old);
	free(old);
	return (new);
}

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
		 free stuff here 
		exit(errno);
	}

	for (i = 0; vect[1][i]; i++) {
		if (vect[1][i] < 48 || vect[1][i] > 57) {
			print_exit_err(vect[1]);
			return;
		}
		status = (status * 10) + (vect[1][i] - 48);
	}

	 free stuff here 
	exit(status);
}

ssize_t _getline(char **buf, int fd) {
	ssize_t r = 0, bytes = 0;
	int buffsize = 1023;
	char readbuf[1024];

	r = read(fd, readbuf, buffsize);
	if (r == 0)
		return (-1);

	*buf = malloc((r + 1) * sizeof(char));
	if (!(*buf)) {
		perror("_getline: buf");
		return (0);
	}
	readbuf[r - 1] = '\0';
	_strcpy(*buf, readbuf);
	bytes += r;
	while (r == buffsize) {
		r = read(fd, readbuf, buffsize);
		readbuf[r - 1] = '\0';
		bytes += r;
		*buf = _realloc(*buf, (bytes + 1));
		_strcat(*buf, readbuf);
	}
	return (bytes);
}
*/
int main(__attribute__((unused)) int ac, __attribute__((unused)) char **av) {
	ssize_t g;
	char *inp = NULL;

	g = _getline(&inp, 0);
	printf("g: %ld\n", g);
	free(inp);
	return (0);
}

