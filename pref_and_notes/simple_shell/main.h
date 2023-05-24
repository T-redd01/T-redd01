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

typedef struct all_builtins
{
	char *builtin_name;
	int (*func_ptr)(state_of_shell *);
} builtin;

/* repl_loop.c */
ssize_t read_inp(char **input);
void repl_loop(state_of_shell *vars);
void sighandler(int sig);

/* eval_all.c */
int eval_inp(state_of_shell *vars, size_t cmds);
void cmd_list_handle(state_of_shell *vars, size_t cmds);

/* built-ins.c */
int built_in_findr(state_of_shell *vars);

/* builtinFuncs.c */
int exit_shell(state_of_shell *vars);
int change_directory(state_of_shell *vars);
int _setenv(state_of_shell *vars);
int print_env(state_of_shell *vars);

/* parser.c */
void exp_parser(state_of_shell *vars);
int num_of_words(char *s);
void sep_args(state_of_shell *vars, int word_idx, int arg_index);
void input_parser(state_of_shell *vars);

/* expand_parse_vars.c */
char *var_exp(state_of_shell *vars, int arg_idx, int *exp_idx);

/* file-stats.c */
int path_findr(state_of_shell *vars);

/* string-utils.c */
size_t _strlen(char *s);
size_t _strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
char *_itoa(size_t *num);
int _strcmp(char *s1, char *s2);

/* string-utils2.c */
ssize_t _atoi(char *s);
char *_strdup(char *src);
int _strcmp_setenv(char *s1, char *s2);

/* write_funcs.c */
size_t _puts(char *s, int fd);

/* path_linked_list.c */
path_list *append_path_node(path_list **h, char *full_path_env, int *st_idx);
path_list *create_path_node(char *full_path_env, int *st_idx);
void print_path_list(path_list **h);
void free_path_list(path_list **h);

/* env-vars.c */
char *_getenv(char *env_var);
size_t matrix_counter(char **matrix);
char *add_env(char *name, char *value);
int err_setenv(char **args);

/* cmd_exec.c */
int execute_cmd(state_of_shell *vars);

/* free_replloop.c */
void free_repl(state_of_shell *vars);
void free_state_args(char **args);

/* free_shell.c */
void free_all(state_of_shell *vars);
void free_environ(void);

#endif