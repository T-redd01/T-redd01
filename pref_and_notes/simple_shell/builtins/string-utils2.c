#include "main.h"

int _atoi(char *s) {
	int i, num = 0;

	if (!s || my_strcmp(s, "0"))
		return (0);

	for (i = 0; s[i]; i++) {
		if (s[i] < 48 || s[i] > 57)
			return (-1);

		if (i == 0) {
			num = s[i] - 48;
		}
		else {
			num *= 10;
			num += (s[i] - 48);
		}
	}
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

