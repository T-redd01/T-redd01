#include "main.h"

size_t tok_val_exp_len(char *tok, size_t err_len, size_t pid_len) {
	size_t i, len = 0;

	if (!tok)
		return (0);

	for (i = 0; tok[i]; i++) {
		if (tok[i] == '$' && tok[i + 1] == '?') {
			len += err_len;
			i++;
			continue;
		}
		if (tok[i] == '$' && tok[i + 1] == '$') {
			len += pid_len;
			i++;
			continue;
		}
		if (tok[i] == '$' && tok[i + 1]) {
			len += _strlen(_getenv((tok + (i + 1))));
			break;
		}
		if (tok[i] == '\0')
			i--;
		len++;
	}
	return (len);
}

tokens *exp_tok(tokens *n) {
	size_t i, j = 0, len = 0, num = 0, pidl = 0, errl = 0;
	char *new = NULL, *pid = NULL, *err = NULL;

	num = getpid();
	pid = _itoa(num);
	pidl = _strlen(pid);
	
	num = errno;
	err = _itoa(num);
	errl = _strlen(err);
	
	len = tok_val_exp_len(n->token, errl, pidl);
	new = malloc((len + 1) * sizeof(char));
	if (!new) {
		perror("exp_tok: new");
		free(pid);
		free(err);
		return (NULL);
	}

	for (i = 0; n->token[i]; i++) {
		if (n->token[i] == '$' && n->token[i + 1] == '?') {
			new[j] = '\0';
			_strcat(new, err);
			j += errl;
			i++;
		} else if (n->token[i] == '$' && n->token[i + 1] == '$') {
			new[j] = '\0';
			_strcat(new, pid);
			j += pidl;
			i++;
		} else if (n->token[i] == '$' && n->token[i + 1]) {
			new[j] = '\0';
			_strcat(new, _getenv((n->token + (i + 1))));
			j += (_strlen(_getenv((n->token + (i + 1)))));
			break;
		} else {
			new[j++] = n->token[i];
		}
		if (n->token[i] == '\0')
			i--;
	}
	new[j] = '\0';
	free(pid);
	free(err);
	free(n->token);
	n->token = new;
	return (n);
}

