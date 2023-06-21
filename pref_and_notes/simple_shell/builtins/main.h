#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

extern char **environ;

typedef struct alias_list {
	char *name;
	char *val;
	struct alias_list *n_al;
} al_list;

typedef struct token_list
{
	char *token;
	struct token_list *n;
} tokens;

typedef struct cmd_vect_list {
	char **vect;
	char sym;
	struct cmd_vect_list *n;
} cmds;

typedef struct shell_cache {
	char *calls;
	al_list *als;
	cmds *commands;
	char **file_vect;
} cache;

typedef struct builtin_commands {
	char *name;
	void (*p)(cache *mm, char **vect);
} builtins;

/* files.c */
int file_arg(cache *mm, char *file_name, char *prog);
void eval_file(cache *mm, char **vect, char *prog);
char **create_arg_vect(int num_args, char *inp);
size_t count_line(char *inp, size_t idx);
int count_inp_vects(char *inp);

/* repl_loop.c */
void repl_loop(cache *mm, char *name);
ssize_t read_inp(char **input);
void sighandler(int sig);

/* eval_cmds.c */
void eval_cmds(cache *mm);
void exec_func(char **vect);

/* builtins.c */
int builtin_findr(cache *mm, char **vect);

/* helpers.c */
int find_delim(char *inp, size_t idx);
size_t matrix_count(char **matrix);
void print_matrix(char **matrix);
void free_matrix(char **matrix);
void _puts(char *str, int fd);

/* helpers2.c */
ssize_t _getline(char **buf, int fd);
char *_realloc(char *old, size_t new_size);
char *call_no(char *prog_name, size_t call);

/* string-utils.c */
int my_strcmp(char *s1, char *s2);
char *_strdup(char *src);
size_t _strlen(char *s);
int _strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);

/* string-utils2.c */
int _atoi(char *s);
char *_itoa(size_t num);

/* env-utils.c */
void init_environ(void);
char *_getenv(char *name);
int key_cmp(char *key, char *name);
void print_env(cache *mm, char **vect);

/* _setenv.c */
char *new_env_var(char *name, char *val);
void replace_env(char *name, char *val);
void _setenv(char *name, char *val);
void call_setenv(cache *mm, char **vect);

/* _unsetenv.c */
void _putchar(char c);
void _unsetenv(char *name);
void call_unsetenv(cache *mm, char **vect);

/* direct.c */
char *_getCWD(size_t num);
void update_oldpwd(char *curr);
void cd_err_msg(char *shell_call, char *tok);
void _change_WD(cache *mm, char **vect);

/* alias_linked_list.c  */
void print_alias_list(al_list *h);
al_list *creat_alias_node(char *key_val);
void prepend_alias_node(al_list **h, al_list *node);
void print_alias_node(al_list *h, char *key);
void free_alias_list(al_list *h);

/* _alias.c  */
char *extract_alias_val(char *pair);
char *extract_alias_name(char *pair);
void _alias(cache *mm, char **vect);

/* shell_exit.c */
void shell_exit(cache *mm, char **vect);
void print_exit_err(char *shell_call, char *num);

/* exp_toks.c */
tokens *exp_tok(tokens *n);
size_t tok_val_exp_len(char *tok, size_t err_len, size_t pid_len);

/* tokens_linked_list.c */
void remove_node(tokens **h, int idx);
void append_tokens_node(tokens **head, tokens *node);
void print_tokens_list(tokens *h);
void free_tokens_list(tokens *h);

/* cmds_linked_list.c */
void free_cmds_list(cmds *h);
void print_cmds_list(cmds *h);
cmds *create_cmds_list(al_list *als, tokens **h);
cmds *append_cmds_node(cmds **head, cmds *node);
cmds *create_cmds_node(al_list *als, tokens *arg_strt, size_t arg_count);

/* parser.c */
char *find_alias(al_list *h, tokens *n);
cmds *parser(al_list *als, char *input);
tokens *create_delim_tok(char *input, size_t *idx);
tokens *create_tok_node(char *inp, size_t idx);

/* find_bin.c */
int find_bin(cmds *node, char *shell_call);
char *create_path(char *n, size_t bin_len, char *path, size_t *idx);
void not_found(char *shell_call, char *name);

#endif

