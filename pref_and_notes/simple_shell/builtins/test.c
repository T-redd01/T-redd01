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

int main(__attribute__((unused)) int ac, __attribute__((unused)) char **av) {
	cmds *head = NULL;
	al_list *als;

	als = malloc(sizeof(al_list));
	als->name = _strdup("c");
	als->val = _strdup("clear");
	als->n_al = NULL;

	head = parser(als, "c echo this and that");
	print_cmds_list(head);
	puts("\n");
	free_cmds_list(head);

	head = parser(als, "c ls c && ls&& cat &&cat || ls|| cat|| echo $? $$ $_ $; ls ; ls ;cat ; ; && && || ||");
	print_cmds_list(head);
	free_cmds_list(head);
	free_alias_list(als);

	/*exp_tok("$PATH");
	printf("Expected: %s\n\n", _getenv("PATH"));

	exp_tok("random$PATH");
	printf("Expected: random%s\n\n", _getenv("PATH"));
	
	exp_tok("random$PATHrandom");
	printf("Expected: random\n\n");

	exp_tok("$random");
	printf("Expected: nil\n\n");

	exp_tok("$");
	printf("Expetedted: $\n\n");

	exp_tok("random$");
	printf("Expected: random$\n\n");

	exp_tok("$?");
	printf("Expected: %d\n\n", errno);

	exp_tok("random$?");
	printf("Expected: random%d\n\n", errno);

	exp_tok("random$?random");
	printf("Expected: random%drandom\n\n", errno);

	exp_tok("$$");
	printf("Expected: %d\n\n", getpid());

	exp_tok("random$$");
	printf("Expected: random%d\n\n", getpid());

	exp_tok("random$$random");
	printf("Expected: random%drandom\n\n", getpid());*/
	return (0);
}

