#include "main.h"

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

void eval_cmds(cache *mm) {
	cmds *start = mm->commands;

	if (!(mm->commands))
		return;

	while (start) {
		if ((builtin_findr(mm, start->vect)) == 0) {
			if ((find_bin(start, mm->calls)))
				exec_func(start->vect);
		}
		
		if (start->sym == '&' && errno != 0) {
			while (start && start->sym == '&')
				start = start->n;
		}

		if (start->sym == '|' && errno == 0) {
			while (start && start->sym == '|')
				start = start->n;
		}
		
		if (start)
			start = start->n;
	}
	free_cmds_list(mm->commands);
}
