#include "main.h"

int find_delim(char *inp, size_t idx) {
    if (inp[idx] == '\0')
        return (1);
    else if (inp[idx] == ' ')
        return (1);
    else if (inp[idx] == ';')
        return (1);
    else if (inp[idx] == '&' && inp[idx + 1] == '&')
        return (1);
    else if (inp[idx] == '|' && inp[idx + 1] == '|')
        return (1);
    else if (inp[idx] == '\n')
        return (1);
    else
        return (0);
}

size_t matrix_count(char **matrix) {
	size_t indices = 0;

	if (!matrix)
		return (0);

	while (matrix[indices])
		indices++;
	return (indices);
}

void print_matrix(char **matrix) {
	size_t i;

	if (!matrix) {
		printf("is nil\n");
		return;
	}

	for (i = 0; matrix[i]; i++)
		printf("%s\n", matrix[i]);
}

void free_matrix(char **matrix) {
	size_t i;

	if (!matrix)
		return;

	for (i = 0; matrix[i]; i++)
		free(matrix[i]);
	free(matrix);
}

void _puts(char *str, int fd) {
	size_t len = 0;

	if (!str)
		return;

	while (str[len])
		len++;

	write(fd, str, len);
}

