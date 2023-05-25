#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

size_t _strlen(char *s)
{
	size_t len = 0;

	if (!s)
		return (0);

	while (s[len])
		len++;
	return (len);
}

char *_strdup(char *src)
{
	char *new;
	int i = 0;

	if (!src)
		return (NULL);

	new = malloc((_strlen(src) + 1) * sizeof(char));
	if (new == NULL)
	{
		perror("_strdup");
		return (NULL);
	}

	while (src[i])
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

typedef struct testing
{
	char **args;
} my_args;

size_t word_counter(char *s)
{
	size_t words = 0, i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] == '#')
			break;
		if (s[i] != ' ' && s[i] != '\n' && s[i])
		{
			words++;
			while (s[i] != ' ' && s[i])
				i++;
			i--;
		}
		if (s[i] == '\0')
			i--;
	}
	return (words);
}

char *var_exp(char *inp, size_t *inp_idx)
{
	size_t i = 0;
	char *exp;

	if (inp[*inp_idx + 1] == '?')
	{
		exp = _strdup("errno:0");
		*inp_idx += 1;
	}
	else if (inp[*inp_idx + 1] == '$')
	{
		*inp_idx += 1;
		exp = _strdup("pid:1234");
	}
	else if (inp[*inp_idx + 1] == '\0' || inp[*inp_idx + 1] == ' ' || inp[*inp_idx + 1] == '\n')
	{
		exp = _strdup("$");
	}
	else
	{
		exp = _strdup("envar/here");
		while (inp[*inp_idx + 1] != ' ' && inp[*inp_idx + 1])
			*inp_idx += 1;
	}
	return (exp);
}

char *arg_adder(char *inp, size_t *idx)
{
	size_t len = 0, buf_idx = 0;
	char *new, buf[4096], *tmp = NULL;

	if (inp[*idx] == '#')
	{
		while (inp[*idx])
			*idx += 1;
		return (NULL);
	}

	while (inp[*idx] != ' ' && inp[*idx] != '\n' && inp[*idx])
	{
		if (inp[*idx] == '$')
		{
			len = 0;
			tmp = var_exp(inp, idx);
			while (tmp[len])
			{
				buf[buf_idx++] = tmp[len];
				len++;
			}
			if (tmp)
			{
				free(tmp);
				tmp = NULL;
			}
		}
		else
		{
			buf[buf_idx++] = inp[*idx];
		}
		*idx += 1;
	}
	*idx -= 1;
	buf[buf_idx] = '\0';
	new = _strdup(buf);
	return (new);
}

void parser(my_args *vars, char *inp)
{
	size_t i, j = 0;
	char *arg;

	vars->args = malloc((word_counter(inp) + 1) * sizeof(char *));
	printf("word_counter: %ld\n", word_counter(inp));
	for (i = 0; inp[i]; i++)
	{
		if (inp[i] != ' ' && inp[i] != '\n' && inp[i])
		{
			vars->args[j++] = arg_adder(inp, &i);
			printf("i: %ld\n", i);
		}
		if (inp[i] == '\0')
		{
			printf("inp[i]: (nil)\n");
			i--;
		}

	}
	vars->args[j] = NULL;
}

int main(void)
{
	int i;

	my_args vars = { NULL };
	char *input = "ls && ls&&ls ls&ls; ls || ls||ls ls|ls ; echo $$ ; echo $?; echo $$$; echo $; echo $test;echo $PATH; cat#ls ;#ls /home/otto/Pictures";
	parser(&vars, "echo $$ #$? $$$ $lsls $");
	for (i = 0; vars.args[i]; i++)
		printf("%s\n", vars.args[i]);
	for (i = 0; vars.args[i]; i++)
		free(vars.args[i]);
	free(vars.args);
	return (0);
}
