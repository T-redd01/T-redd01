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

void _strdup(char *dest, char *src)
{
	int i;

	if (!src)
		return;
	dest = malloc((_strlen(src) + 1) * sizeof(char));
	for (i = 0; src[i]; i++)
		dest[i] = src[i];
	dest[i] = '\0';
}