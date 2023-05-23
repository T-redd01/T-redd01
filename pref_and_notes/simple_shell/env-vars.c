#include "main.h"

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