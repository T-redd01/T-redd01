#include "main.h"

char *_strcat(__attribute__((unused)) char *dest, __attribute__((unused)) char *src) {
	return (NULL);
}

/* expanding tokens */
char *exp_alias(al_list *h, char *key) {
	if (!h || !key)
		return (NULL);

	while (h) {
		if ((my_strcmp(h->name, key)))
			return (h->val);
		h = h->n_al;
	}
	return (NULL);
}

size_t exp_val_len(char *word, int *flag) {
	size_t i, pid_len, err_len, len = 0;
	char *err = NULL, *pid = NULL;

	if (!word || !flag)
		return (0);

	err = _strdup("123"); /*_itoa(errno);*/
	err_len = 3; /*_strlen(err);*/
	pid = _strdup("525"); /*_itoa(getpid());*/
	pid_len = 3; /*_strlen(pid);*/
	for (i = 0; word[i]; i++) {
		if (word[i] == '$' && word[i + 1] == '?') {
			*flag = 1;
			len += err_len;
			i++;
		} else if (word[i] == '$' && word[i + 1] == '$') {
			*flag = 1;
			len += pid_len;
			i++;
		} else if (word[i] == '$' && word[i + 1]) {
			len += 1;
		}
	}
	free(err);
	free(pid);
	return (len);
}

char *_spec_val(char *word) {
	size_t i, pid_len, err_len, j = 0, len = 0;
	int flag = 0;
	char *var = NULL, *err = NULL, *pid = NULL;

	if (!word)
		return (NULL);

	len = exp_val_len(word, &flag);
	if (!flag || !len)
		return (NULL);

	err = _strdup("123"); /*_itoa(errno);*/
	err_len = 3; /*_strlen(err);*/
	pid = _strdup("525"); /*_itoa(getpid());*/
	pid_len = 3; /*_strlen(pid);*/

	var = malloc((len + 1) * sizeof(char));
	if (!var) {
		free(err);
		free(pid);
		perror("_spec_val: var");
		return (NULL);
	}
	for (i = 0; word[i]; i++) {
		if (word[i] == '$' && word[i + 1] == '?') {
			var[j] = '\0';
			_strcat(var, err);
			j += (err_len + 1);
			i++;
		} else if (word[i] == '$' && word[i + 1] == '$') {
			var[j] = '\0';
			_strcat(var, pid);
			j += (pid_len + 1);
			i++;
		} else {
			var[j++] = word[i];
		}
	}
	var[j] = '\0';
	free(pid);
	free(err);
	printf("var: %s\n", var);
	return (NULL);
}

char *_env_val(__attribute__((unused)) char *word) {
	/* make env here */
	return (NULL);
}

char *exp_key(al_list *h, char *word) {
	char *val = NULL;

	if (!word)
		return (NULL);

	if (word[0] == '$' && word[1] == '\0')
		return ((_strdup("$")));

	val = exp_alias(h, word);
	if (val)
		return (val);

	val = _spec_val(word);
	if (val)
		return (val);

	val = _env_val(word);
	if (val)
		return (val);
	return (NULL);
}

