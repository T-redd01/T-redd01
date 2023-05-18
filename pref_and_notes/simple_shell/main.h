#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>

extern char **environ;
extern int errno;

typedef struct all_path
{
	char *bin_paths;
	int bin_paths_len;
	struct all_path *next;
} path_list;

typedef struct holder
{
	char *prog_name;
	char *err_prmpt;
	char *inpbuf;
	char **args;
	char *cmd;
	path_list *path_env;
} state_of_shell;

/* repl_loop.c */
ssize_t read_inp(char **input);
void repl_loop(state_of_shell *vars);
void sighandler(int sig);

/* eval_all.c */
int eval_inp(state_of_shell *vars, size_t cmds);
void cmd_list_handle(state_of_shell *vars, size_t cmds);

/* parser.c */
int num_of_words(char *s);
void sep_args(state_of_shell *vars, int word_idx, int arg_index);
void input_parser(state_of_shell *vars);

/* file-stats.c */
int path_findr(state_of_shell *vars);

/* string-utils.c */
size_t _strlen(char *s);
size_t _strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
char *_itoa(size_t *num);
size_t _puts(char *s);

/* path_linked_list.c */
path_list *append_path_node(path_list **h, char *full_path_env, int *st_idx);
path_list *create_path_node(char *full_path_env, int *st_idx);
void print_path_list(path_list **h);
void free_path_list(path_list **h);

/* env-vars.c */
char *_getenv(char *env_var);

/* cmd_exec.c */
int execute_cmd(state_of_shell *vars);

/* free_replloop.c */
void free_repl(state_of_shell *vars);
void free_state_args(char **args);

/* free_shell.c */
void free_all(state_of_shell *vars);

#endif