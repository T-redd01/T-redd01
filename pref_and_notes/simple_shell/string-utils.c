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
	{
		/*printf("dest: %c - src: %c\n", dest[i], src[i]);*/
		dest[i] = src[i];
	}
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
	{
		/*printf("dest: %c - src: %c\n", dest[i], src[i]);*/
		dest[i] = src[j];
	}
	dest[i] = '\0';
	return (dest);
}

char *_itoa(size_t *num)
{
	size_t holder = *num, counter = 0;
	ssize_t i;
	char *dig;

	if (!num)
		return ("0");

	while (holder)
	{
		counter++;
		holder /= 10;
	}

	dig = malloc((counter + 1) * sizeof(char));
	for (i = (counter - 1); i >= 0; i--)
	{
		holder = *num % 10;
		*num /= 10;
		dig[i] = ('0' + holder);
	}
	dig[counter] = '\0';
	*num = counter;
	return (dig);
}

size_t _puts(char *s)
{
	size_t len = _strlen(s);

	if (!s)
		return (0);
	write(1, s, len);
	return (len);
}