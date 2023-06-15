#include "main.h"

/* extra funcs */
void exec_func(char **vect) {
	int pid;

	pid = fork();
	if (pid == 0) {
		if ((execve(vect[0], vect, environ)) == -1) {
			perror("exec_func: execve");
			return;
		}
	} else {
		wait(NULL);
	}
}

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

int main(__attribute__((unused)) int ac, char **av) {
	int fd, r;
	char buf[1024];

	if (ac == 2) {
		fd = open(av[1], O_RDONLY);
		if (fd == -1) {
			perror("open");
			return (1);
		}
		r = read(fd, buf, 1024);
		write(1, buf, r);
	}
	return (0);
}

