#include "shell.h"

/**
*e_puts - write an input string
 *@str: string to be printed
 *Return: void
 */
void e_puts(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		e_putchar(str[j]);
		j++;
	}
}

/**
 *e_putchar - print char ch to stderr
 * @ch: char to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set.
 */
int e_putchar(char ch)
{
	static int j;
	static char bufer[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, bufer, j);
		j = 0;
	}
	if (ch != BUF_FLUSH)
		bufer[j++] = ch;
	return (1);
}

/**
 *put_fd - prints chara ch to fd
 *@ch: chara to print
 *@f_d:filedescriptor to write to
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int put_fd(char ch, int f_d)
{
	static int j;
	static char bufer[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(f_d, bufer, j);
		j = 0;
	}
	if (ch != BUF_FLUSH)
		bufer[j++] = ch;
	return (1);
}
