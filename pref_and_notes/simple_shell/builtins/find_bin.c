#include "main.h"

void not_found(char *shell_call, char *name) {
	if (errno == 2) {
		_puts(shell_call, 2);
		_puts(name, 2);
		_puts(": not found\n", 2);
		errno = 127;
		return;
	}
	_puts(shell_call, 2);
	perror(name);
}

char *create_path(char *n, size_t bin_len, char *path, size_t *idx) {
	char *search = NULL;
	size_t i = *idx, j = 0, len = 0;

	if (!path || !n)
		return (NULL);

	while (path[*idx] && path[*idx] != ':') {
		len++;
		*idx += 1;
	}

	search = malloc((len + bin_len + 2) * sizeof(char));
	if (!search) {
		perror("bin_exists: search");
		return (NULL);
	}

	while (path[i] && path[i] != ':')
		search[j++] = path[i++];
	search[j] = '\0';
	_strcat(search, "/");
	_strcat(search, n);
	return (search);
}

int find_bin(cmds *node, char *shell_call) {
	size_t i, bin_len = 0;
	char *path = NULL, *search = NULL;
	struct stat buf;

	if (!node || !(node->vect[0]))
		return (0);

	if ((stat(node->vect[0], &buf)) == 0)
		return (1);

	path = _getenv("PATH");
	if (!path)
		return (0);

	bin_len = _strlen(node->vect[0]);
	for (i = 0; path[i]; i++) {
		if (path[i] && path[i] != ':') {
			search = create_path(node->vect[0], bin_len, path, &i);
			if (!(stat(search, &buf))) {
				free(node->vect[0]);
				node->vect[0] = search;
				return (1);
			}
			free(search);
		}
		if (path[i] == '\0')
			i--;
	}
	not_found(shell_call, node->vect[0]);
	return (0);
}

