#include "main.h"

size_t _puts(char *s, int fd)
{
	size_t len = _strlen(s);

	if (!s)
		return (0);
	write(fd, s, len);
	return (len);
}