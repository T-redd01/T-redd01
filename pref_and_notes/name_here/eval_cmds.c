#include "main.h"

void exec_func(char *cmd, char **vect) {
	pid_t cpid;
	int wstatus;

	cpid = fork();
	if (cpid == 0) {
		if ((execve(cmd, vect, environ)) == -1) {
			perror("exec_func: execve");
			return;
		}
	} else {
		wait(&wstatus);
		errno = WEXITSTATUS(wstatus);
	}
}

void to_chain(cache *mm) {
	if (!mm || !(mm->commands))
		return;

	if (mm->commands->sym == '|' && errno == 0)
		mm->chain = 0;
	else if (mm->commands->sym == '&' && errno != 0)
		mm->chain = 0;
	else
		mm->chain = 1;
}

void run_eval(cache *mm) {
    if (!mm || !(mm->toks))
        return;

    mm->commands = create_cmds_list(mm->als, &(mm->toks));
    free_tokens_list(mm->toks);
    mm->toks = NULL;
    eval_cmds(mm);
    to_chain(mm);
    free_cmds_list(mm->commands);
    mm->commands = NULL;
}

void eval_cmds(cache *mm) {
	cmds *start = mm->commands;

	if (!(mm->commands))
		return;

	if (mm->chain == 0)
		return;

	while (start) {
		if ((builtin_findr(mm, start->vect)) == 0) {
			if ((find_bin(&(mm->cmd), start, mm->calls)))
				exec_func(mm->cmd, start->vect);
		}
		
		if (start)
			start = start->n;
	}
	if (mm->cmd) {
		free(mm->cmd);
		mm->cmd = NULL;
	}

}
