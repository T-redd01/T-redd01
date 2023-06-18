#include "main.h"

int _atoi(char *s) {
	int i = 0, flag = 0, num = 0;

	if (!s || my_strcmp(s, "0"))
		return (0);

	if (s[i] == '-') {
		flag = 1;
		i = 1;
	}

	for (; s[i]; i++) {
		if (s[i] < 48 || s[i] > 57)
			return (-1);
		num = (num * 10) + (s[i] - 48);
	}

	if (flag)
		num *= -1;
	return (num);
}

char *_itoa(size_t num) {
	size_t i, len = 0, tmp = num;
	char *str = NULL;

	if (num == 0)
		return ((_strdup("0")));

	while (tmp) {
		len++;
		tmp /= 10;
	}

	str = malloc((len + 1) * sizeof(char));
	if (!str) {
		perror("_itoa: str");
		return (NULL);
	}

	i = len;
	str[i--] = '\0';
	while (num) {
		str[i] = '0' + (num % 10);
		num /= 10;
		i--;
	}
	return (str);
}

