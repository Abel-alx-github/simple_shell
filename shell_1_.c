#include "shell.h"
/**
 *history_ - shows the history list.
 *@para: Structure containing parpmeter.
 * Return: Always 0
 */
int history_(para_t *para)
{
	printlist(para->history);
	return (0);
}
/**
 * isdelim - look for if character is a delimeter
 * @c: char to  look
 * @delimter: the delimeter
 * Return: 1 if true, 0 if false
 */
int isdelimter(char c, char *delimter)
{
	while (*delimter)
		if (*delimter++ == c)
			return (1);
	return (0);
}

/**
 *is_alpha - looks for alphabetic
 *@ch: char to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int is_alpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *a_toi - converts a string to an integer
 *@str: string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int a_toi(char *str)
{
	int j, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (j = 0;  str[j] != '\0' && flag != 2; j++)
	{
		if (str[j] == '-')
			sign *= -1;

		if (str[j] >= '0' && str[j] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[j] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
