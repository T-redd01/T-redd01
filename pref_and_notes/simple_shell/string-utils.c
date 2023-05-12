#include "main.h"

size_t _strlen(char *s)
{
	size_t len = 0;

	while (s[len++])
		;
	return (len - 1);
}