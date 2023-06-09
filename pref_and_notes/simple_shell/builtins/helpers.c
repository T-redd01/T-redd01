#include "main.h"

char *_strdup(char *src) {
	size_t i, len = 0;
	char *new = NULL;

	if (!src)
		return (NULL);

	while (src[len])
		len++;

	new = malloc((len + 1) * sizeof(char));
	if (!new) {
		perror("_strdup");
		return (NULL);
	}

	for (i = 0; src[i]; i++)
		new[i] = src[i];
	new[i] = '\0';
	return (new);
}

int my_strcmp(char *s1, char *s2) {
        size_t i;

        if (!s1 || !s2)
                return (0);

        for (i = 0; s1[i] && s2[i]; i++) {
                if (s1[i] != s2[i])
                        return (0);
        }
        if (s1[i] != s2[i])
                return (0);
        return (1);
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

