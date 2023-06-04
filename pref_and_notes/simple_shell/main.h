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

typedef struct token_list
{
	char *token;
	struct token_list *n;
} tokens;

typedef struct cmd_list
{
	char **args;
	char chain_symbol;
	struct cmd_list *n_cmd;
} cmd_buf;

typedef struct holder
{
	char *prog_name;
	char *err_prmpt;
	char *inpbuf;
	char *cmd;
	char **args;
	path_list *path_env;
	cmd_buf *all_cmds;
} state_of_shell;

typedef struct all_builtins
{
	char *builtin_name;
	int (*func_ptr)(char **vect, char *err_str);
} builtin;

/* repl_loop.c */
ssize_t read_inp(char **input);
void repl_loop(state_of_shell *vars);
void sighandler(int sig);

/* eval_all.c */
int eval_inp(state_of_shell *vars, size_t cmds);
void cmd_list_handle(state_of_shell *vars, size_t cmds, cmd_buf *h);

/* built-ins.c */
void change_dir_env(void);
int built_in_findr(char **vect, char *err_str);

/* builtinFuncs.c */
int exit_shell(char **vect, char *err_str);
int change_directory(char **vect, char *err_str);
int call_setenv(char **vect, char *err_str);
int print_env(char **vect, char *err_str);
int _unsetenv(char **vect, char *err_str);

/*******************************work on parser here******************/
/* parser.c */
void exp_parser(state_of_shell *vars);
int num_of_words(char *s);
void sep_args(state_of_shell *vars, int word_idx, int arg_index);
void input_parser(state_of_shell *vars);

/* newparser.c */
tokens *add_tokens_node_end(tokens **head, char *src);
void print_tokens_list(tokens *h);
void free_tokens_list(tokens *h);
int find_delim(char *inp, size_t idx);
tokens *new_list(char *inp);
void remove_node(tokens **h, int idx);
char *exp_var(char *s);
void find_var(tokens **head);
cmd_buf *create_cmd_buf_node(tokens *arg_strt, size_t arg_count);
cmd_buf *append_cmd_buf_node(cmd_buf **head, cmd_buf *node);
cmd_buf *create_cmd_buf(tokens **h);
void print_cmd_list(cmd_buf *h);
void free_cmd_list(cmd_buf *h);
/*******************************work on parser here******************/

/* expand_parse_vars.c */
char *var_exp(state_of_shell *vars, int arg_idx, int *exp_idx);

/* file-stats.c */
int path_findr(state_of_shell *vars, char **vect);

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
int _setenv(char *name, char *value);

/* cmd_exec.c */
int execute_cmd(state_of_shell *vars, char **vect);

/* free_replloop.c */
void free_repl(state_of_shell *vars);
void free_state_args(char **args);

/* free_shell.c */
void free_all(state_of_shell *vars);
void free_environ(void);

#endif