#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/wait.h>

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

/* helpers.c */
int my_strcmp(char *s1, char *s2);
char *_strdup(char *src);
size_t matrix_count(char **matrix);
void print_matrix(char **matrix);
void free_matrix(char **matrix);

/* env-utils.c */
void init_environ(void);
char *_getenv(char *name);
int key_cmp(char *key, char *name);

/* _setenv.c */
char *new_env_var(char *name, char *val);
void replace_env(char *name, char *val);
void _setenv(char *name, char *val);

/* _unsetenv.c */
void _unsetenv(char *name);

/* direct.c */
char *_getCWD();
void update_oldpwd(char *curr);
void _change_WD(char *dest);

/* alias_linked_list.c  */
void print_alias_list(al_list *h);
al_list *creat_alias_node(char *key_val);
void prepend_alias_node(al_list **h, al_list *node);
void print_alias_node(al_list *h, char *key);
void free_alias_list(al_list *h);

/* _alias.c  */
char *extract_alias_val(char *pair);
char *extract_alias_name(char *pair);
void _alias(al_list **h, char **vect);

/* exp_toks.c */
char *exp_alias(al_list *h, char *key);
size_t exp_val_len(char *word, int *flag);
char *_spec_val(char *word);
char *_env_val(char *word);
char *exp_key(al_list *h, char *word);

/* tokens_linked_list.c */
void remove_node(tokens **h, int idx);
tokens *append_tokens_node(tokens **head, tokens *node);
void print_tokens_list(tokens *h);
void free_tokens_list(tokens *h);

#endif

