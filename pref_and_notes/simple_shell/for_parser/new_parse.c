#include <stdio.h>
#include <stdlib.h>

size_t _strlen(char *s)
{
	size_t len = 0;

	if (!s)
		return (0);
	while (s[len++])
		;
	return (len - 1);
}

char *_strdup(char *src)
{
	int i;
	char *dest;

	if (!src)
		return (NULL);

	dest = malloc((_strlen(src) + 1) * sizeof(char));
	for (i = 0; src[i]; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

typedef struct testing
{
	char **args;
} my_args;

typedef struct word_args
{
	char *arg;
	struct word_args *n;
} arg_list;

arg_list *create_arg_node(char *s)
{
	arg_list *new = NULL;

	if (!s)
		return (NULL);

	new = malloc(sizeof(arg_list));
	if (!new)
		return (NULL);

	new->arg = _strdup(s);
	new->n = NULL;
	return (new);
}

arg_list *add_arg_node_end(arg_list **h, arg_list *node)
{
	arg_list *tmp = *h;

	if (!node)
		return (NULL);

	if (*h == NULL)
	{
		*h = node;
		return (node);
	}

	while (tmp->n)
		tmp = tmp->n;
	tmp->n = node;
	return (node);
}

size_t count_arg_nodes(arg_list *h)
{
	size_t num = 0;

	while (h)
	{
		num++;
		h = h->n;
	}
	return (num);
}

void print_arg_list(arg_list *h)
{
	int i = 0;
	while (h)
	{
		i++;
		printf("node %d: %s\n", i, h->arg);
		h = h->n;
	}
}

int word_counter(char *s)
{
	int words = 0, i = 0;

	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\n')
		{
			words++;
			while (s[i] != ' ' && s[i] != '\0' && s[i] != '\n')
				i++;
			i--;
		}
		i++;
	}
	return (words);
}

char **word_seperator(char *inp)
{
	size_t i = 0, tmp, len, matrix_ind = 0, j;
	char **matrix;

	if (!inp)
		return (NULL);

	matrix = malloc((word_counter(inp) + 1) * sizeof(char *));
	while (inp[i])
	{
		if (inp[i] != ' ' && inp[i] != '\n')
		{
			len = 0;
			tmp = i;
			while (inp[tmp] && inp[tmp] != '\n' && inp[tmp] != ' ')
			{
				len++;
				tmp++;
			}
			matrix[matrix_ind] = malloc((len + 1) * sizeof(char));
			j = 0;
			while (inp[i] && inp[i] != '\n' && inp[i] != ' ')
				matrix[matrix_ind][j++] = inp[i++];
			matrix[matrix_ind++][j] = '\0';
		}
		if (inp[i] == '\0')
			i--;
		i++;
	}
	matrix[matrix_ind] = NULL;
	return (matrix);
}

int main(void)
{

	/*my_args vars = {NULL};*/
	int i;
	char **sep_args;
	char *input = "ls && ls&&ls ls&ls;ls || ls||ls ls|ls ; echo $$ ; echo $?; echo $$$; echo $; echo $test;echo $PATH; cat#ls ;#ls /home/otto/Pictures";

	sep_args = word_seperator(input);
	for (i = 0; sep_args[i]; i++)
	{
		printf("%s\n", sep_args[i]);
		free(sep_args[i]);
	}
	free(sep_args);
	return (0);
}
