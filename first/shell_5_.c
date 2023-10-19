#include "shell.h"
/**
 *puts_fd - writetst string
 * @str: be printed
 *@f_d: descriptor to write to
 *Return: the number of chars put
 */
int puts_fd(char *str, int f_d)
{
	int j = 0;

	if (!str)
		return (0);
	while (*str)
	{
		j += put_fd(*str++, f_d);
	}
	return (j);
}
/**
 *erra_toi - converts a string to an integer
 *@str: string be converted
 * Return: if no numbers in string zeri, otherwise -1 on error
 */
int erra_toi(char *str)
{
	int j = 0;
	unsigned long int output = 0;

	if (*str == '+')
		str++;
	for (j = 0;  str[j] != '\0'; j++)
	{
		if (str[j] >= '0' && str[j] <= '9')
		{
			output *= 10;
			output += (str[j] - '0');
			if (output > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (output);
}

/**
 * printerror - write error message
 * @para: parameter
 * @estr:containing specified error type
 * Return:  if no numbers in string zero, otherwise-1
 */
void printerror(para_t *para, char *estr)
{
	e_puts(para->filename);
	e_puts(": ");
	printd(para->linecount, STDERR_FILENO);
	e_puts(": ");
	e_puts(para->argv[0]);
	e_puts(": ");
	e_puts(estr);
}

/**
 * printd - wwrite nteger number
 * @input: the input
 * @f_d: the filedescriptor to write to
 * * Return: number of characters printed
 */
int printd(int input, int f_d)
{
	int (*__putchar)(char) = putcha_r;
	int j, count = 0;
	unsigned int abs_, current;

	if (f_d == STDERR_FILENO)
		__putchar = e_putchar;
	if (input < 0)
	{
		abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		abs_ = input;
	current = abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (abs_ / j)
		{
			__putchar('0' + current / j);
			count++;
		}
		current %= j;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convertnumber - converter itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convertnumber(long int num, int base, int flags)
{
	static char *arr;
	static char buf[50];
	char sign = 0;
	char *pt;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pt = &buf[49];
	*pt = '\0';

	do	{
		*--pt = arr[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--pt = sign;
	return (pt);
}

/**
 * removecomments - places first instance of '#' with '\0'
 * @bufer: the string to modify
 * * Return: Always 0 on succes
 */
void removecomments(char *bufer)
{
	int j;

	for (j = 0; bufer[j] != '\0'; j++)
		if (bufer[j] == '#' && (!j || bufer[j - 1] == ' '))
		{
			bufer[j] = '\0';
			break;
		}
}
