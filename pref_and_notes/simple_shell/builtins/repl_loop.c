#include "main.h"

void sighandler(__attribute__((unused)) int sig) {
	errno = 130;
	_puts("\n$ ", 1);
}

ssize_t read_inp(char **input) {
	ssize_t rline;

	if (isatty(STDIN_FILENO))
	{
		_puts("$ ", 1);
	}
	rline = _getline(input, 0);
	return (rline);
}

void repl_loop(cache *mm, char *name) {
	ssize_t retval;
	size_t cmds = 0;
	char *inp = NULL;

	signal(SIGINT, &sighandler);
	while (1) {
		cmds++;
		retval = read_inp(&inp);
		if (retval == -1) {
			if (isatty(STDIN_FILENO))
				_puts("\n", 1);
			free_matrix(environ);
			free_alias_list(mm->als);
			exit(errno);
		}

		if (retval == 1 && *inp == '\n') {
			free(inp);
			continue;
		}
		mm->commands = parser(mm->als, inp);
		free(inp);
		mm->calls = call_no(name, cmds);
		eval_cmds(mm);
		free(mm->calls);
	}
}

