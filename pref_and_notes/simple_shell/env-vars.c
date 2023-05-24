#include "main.h"

size_t matrix_counter(char **matrix)
{
	size_t count = 0;

	while (matrix[count])
		count++;
	return (count);
}

char *_getenv(char *env_var)
{
	int i, j, flag = 1;
	char *found;

	for (i = 0; environ[i]; i++)
	{
		j = 0;
		while (environ[i][j] != '=' || env_var[j] != '\0')
		{
			if (environ[i][j] != env_var[j])
			{
				flag = 1;
				break;
			}
			j++;
		}
		if (flag == 0)
		{
			found = environ[i];
			return (found + j + 1); /* remove name and '=' */
		}
		flag = 0;
	}
	return (NULL);
}

char *add_env(char *name, char *value)
{
	size_t i, j = 0;
	char *new_env;
	if (!name || !value)
		return (NULL);
	new_env = malloc((_strlen(name) + _strlen(value) + 2) * sizeof(char));
	for (i = 0; name[i]; i++)
		new_env[j++] = name[i];
	new_env[j++] = '=';
	for (i = 0; value[i]; i++)
		new_env[j++] = value[i];
	new_env[j] = '\0';
	return (new_env);
}

int err_setenv(char **args)
{
	size_t i;

	for (i = 0; args[i]; i++)
	{
		if (i == 3)
		{
			_puts("Usage: setenv [NAME] [VALUE]\n", 2);
			return (1);
		}
	}

	if (!args[1] || !args[2])
	{
		_puts("Usage: setenv [NAME] [VALUE]\n", 2);
		return (1);
	}
	return (0);
}

int _setenv(char *name, char *value)
{
	int i, flag = 0, idx = -1;
	char **holder;

	holder = malloc((matrix_counter(environ) + 1) * sizeof(char *));
	for (i = 0; environ[i]; i++)
	{
		if ((flag = _strcmp_setenv(environ[i], name)))
			idx = i;
		holder[i] = _strdup(environ[i]);
	}
	holder[i] = NULL;

	free_environ();
	if (idx != -1)
		environ = malloc((matrix_counter(holder) + 1) * sizeof(char *));
	else
		environ = malloc((matrix_counter(holder) + 2) * sizeof(char *));
	for (i = 0; holder[i]; i++)
	{
		if (i == idx)
		{
			environ[i] = add_env(name, value);
			continue;
		}
		environ[i] = _strdup(holder[i]);
	}
	if (idx == -1)
		environ[i++] = add_env(name, value);
	environ[i] = NULL;

	for (i = 0; holder[i]; i++)
		free(holder[i]);
	free(holder);
	return (1);
}