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

void repl_loop(cache *mm) {
	ssize_t g = 0;
	size_t cmds = 0;

	signal(SIGINT, &sighandler);
	while (1) {
		mm->chain = 1;
		cmds++;
		g = read_inp(&(mm->inp));
		if (g == -1) {
			if (isatty(STDIN_FILENO))
				_puts("\n", 1);
			free_matrix(environ);
			free_alias_list(mm->als);
			exit(errno);
		}

		if (g == 1 && *(mm->inp) == '\n') {
			free(mm->inp);
			continue;
		}
		mm->calls = call_no(mm->name, cmds);
		parser(mm, mm->inp);
		free(mm->inp);
		free(mm->calls);
	}
}

