#include "main.h"

ssize_t _atoi(char *s)
{
	int i;
	ssize_t num;

	if (!s)
		return (-1);

	for (i = 0; s[i]; i++)
	{
		if (s[i] < 48 || s[i] > 57)
			return (-1);

		if (i == 0)
		{
			num = s[i] - 48;
		}
		else
		{
			num *= 10;
			num += (s[i] - 48);
		}
	}
	return (num);
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

int _strcmp_setenv(char *s1, char *s2)
{
	int i, ret = 0;

	if (s1 == NULL || s2 == NULL)
		return (0);

	for (i = 0; s2[i]; i++)
	{
		if (s1[i] == s2[i])
			ret = 1;
		else
			return (0);

		if (s1[i] == '=' && s2[i] != '\0')
			return (0);

		if (s1[i] != '=' && s2[i] == '\0')
			return (0);
	}
	return (ret);
}
