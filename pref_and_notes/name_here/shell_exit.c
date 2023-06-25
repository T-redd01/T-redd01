#include "main.h"

void print_exit_err(char *shell_call, char *num) {
	if (!num)
		return;

	_puts(shell_call, 2);
	_puts("exit: Illegal number: ", 2);
	_puts(num, 2);
	_puts("\n", 2);
}

void free_shell_cache(cache *mm) {
	if (!mm)
		return;

	free_matrix(environ);
	free_matrix(mm->file_vect);
	free_alias_list(mm->als);
	free_cmds_list(mm->commands);
	free(mm->inp);
	free(mm->calls);
	free_tokens_list(mm->toks);
}

void shell_exit(cache *mm, char **vect) {
	int i, status = 0;

	if (!vect[1]) {
		free_shell_cache(mm);
		exit(errno);
	}

	for (i = 0; vect[1][i]; i++) {
		if (vect[1][i] < 48 || vect[1][i] > 57) {
			print_exit_err(mm->calls, vect[1]);
			return;
		}
		status = (status * 10) + (vect[1][i] - 48);
	}
	free_shell_cache(mm);
	exit(status);
}

