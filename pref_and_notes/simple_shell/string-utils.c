#include "main.h"

size_t _strlen(char *s)
{
	size_t len = 0;

	if (!s)
		return (0);
	while (s[len++])
		;
	return (len - 1);
}

size_t _strcpy(char *dest, char *src)
{
	size_t len = 0, i;

	if (src == NULL)
		return (1);

	len = _strlen(src);
	for (i = 0; i < len; i++)
		dest[i] = src[i];
	src[i] = '\0';
	return (0);
}

char *_strcat(char *dest, char *src)
{
	size_t i, j;

	if (!dest || !src)
		return (NULL);

	for (i = 0; dest[i]; i++)
		;
	for (j = 0; src[j]; j++, i++)
		dest[i] = src[j];
	dest[i] = '\0';
	return (dest);
}