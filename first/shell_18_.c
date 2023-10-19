#include "shell.h"

/**
 *str_dup - duplicates a string
 *@str:string to duplicate
 *Return:duplicated string
 */
char *str_dup(const char *str)
{
	int len = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (len++; len--;)
		ret[len] = *--str;
	return (ret);
}

/**
 *put_s - write input string
 *@str: string to be written
 *Return: void
 */
void put_s(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		putcha_r(str[j]);
		j++;
	}
}

/**
 * putcha_r - print one char
 *@ch: chara to print
 *Return: On success 1. otherwise -1.
 */
int putcha_r(char ch)
{
	static int i;
	static char bufer[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, bufer, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		bufer[i++] = ch;
	return (1);
}
