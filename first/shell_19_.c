#include "shell.h"

/**
 *str_tow - toknixes. Repeat delimiters are ignored
 * @str: string
 * @del: delimeter
 * Return: a pointer of strings, or NULL on failure
 */

char **str_tow(char *str, char *del)
{
	int i, j, n, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!del)
		del = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!isdelimter(str[i], del) && (isdelimter(str[i + 1], del) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (isdelimter(str[i], del))
			i++;
		n = 0;
		while (!isdelimter(str[i + n], del) && str[i + n])
			n++;
		s[j] = malloc((n + 1) * sizeof(char));
		if (!s[j])
		{
			for (n = 0; n < j; n++)
				free(s[n]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < n; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **str_tow2 - string into words
 * @str: string
 * @del: delimeter
 * Return: a pointer to strings, or NULL on failure
 */
char **str_tow2(char *str, char del)
{
	int i, n, m, j, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != del && str[i + 1] == del) ||
		    (str[i] != del && !str[i + 1]) || str[i + 1] == del)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == del && str[i] != del)
			i++;
		n = 0;
		while (str[i + n] != del && str[i + n] && str[i + n] != del)
			n++;
		s[j] = malloc((n + 1) * sizeof(char));
		if (!s[j])
		{
			for (n = 0; n < j; n++)
				free(s[n]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < n; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
