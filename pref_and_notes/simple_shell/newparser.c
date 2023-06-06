#include "main.h"

int find_delim(char *inp, size_t idx)
{
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

tokens *new_list(char *inp)
{
	size_t i, bufidx = 0;
	char buffer[4096];
	tokens *head = NULL;

	if (!inp)
		return (NULL);

	for (i = 0; inp[i]; i++)
	{
		if (!(find_delim(inp, i)))
		{
			if (inp[i] == '#')
				break;
			bufidx = 0;
			while (!(find_delim(inp, i)))
			{
				buffer[bufidx++] = inp[i];
				i++;
			}
			buffer[bufidx] = '\0';
			add_tokens_node_end(&head, buffer);
			i--;
		}
		if (inp[i] == ';')
			add_tokens_node_end(&head, ";");
		if (inp[i] == '&' && inp[i + 1] == '&')
		{
			add_tokens_node_end(&head, "&&");
			i++;
		}
		if (inp[i] == '|' && inp[i + 1] == '|')
		{
			add_tokens_node_end(&head, "||");
			i++;
		}
		if (inp[i] == '\0')
			i--;
	}
	return (head);
}

char *exp_var(char *s)
{
	size_t i, j, buf_idx = 0, num;
	char buffer[4096], env[4096], *var = NULL;

	for (i = 0; s[i]; i++)
	{
		j = 0;
		if (s[i] == '$' && s[i + 1] == '$')
		{
			num = getpid();
			var = _itoa(&num);
			while (var[j])
				buffer[buf_idx++] = var[j++];
			i++;
			free(var);
		}
		else if (s[i] == '$' && s[i + 1] == '?')
		{
			num = errno;
			var = _itoa(&num);
			while (var[j])
				buffer[buf_idx++] = var[j++];
			i++;
			free(var);
		}
		else if (s[i] == '$' && (s[i + 1] == '\0' || s[i + 1] == '='))
		{
			buffer[buf_idx++] = '$';
		}
		else if (s[i] == '$' && s[i + 1])
		{
			i++;
			while (s[i] && s[i] != '=')
				env[j++] = s[i++];
			env[j] = '\0';
			i--;
			var = _strdup(_getenv(env));
			if (var)
			{
				j = 0;
				while (var[j])
					buffer[buf_idx++] = var[j++];
			}
			free(var);
		}
		else
		{
			buffer[buf_idx++] = s[i];
		}
		if (s[i] == '\0')
			i--;
	}
	buffer[buf_idx] = '\0';
	if (buffer[0] == '\0')
		return (NULL);
	var = _strdup(buffer);
	return (var);
}

void find_var(tokens **head)
{
	int i, idx = 0;
	char *new_str = NULL;
	tokens *tmp = *head, *move_to = NULL;

	if (!(*head))
		return;

	while (tmp)
	{
		move_to = tmp->n;
		for (i = 0; tmp->token[i]; i++)
		{
			if (tmp->token[i] == '$')
			{
				new_str = exp_var(tmp->token);
				if (new_str)
				{
					free(tmp->token);
					tmp->token = _strdup(new_str);
					free(new_str);
				}
				else
				{
					remove_node(head, idx);
					idx--;
				}
				break;
			}
		}
		idx++;
		tmp = move_to;
	}
}
