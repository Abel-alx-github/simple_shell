#include "shell.h"

/**
 *str_len - returns the length of characters
 *@str: the string to count
 *
 * Return: length of string
 */
int str_len(char *str)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str++)
		i++;
	return (i);
}
/**
 *str_cmp - performs lexicogarphic comparison of two strangs.
 * @str1: first strang
 * @str2: second strang
 *
 * Return: negative if str1 < str2, positive if str1 > str2, 0 if str1 == str2
 */
int str_cmp(const char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}
/**
 *str_cat - concatenates two strings
 * @dest: the destination pointer
 * @src: the source pointer
 *
 * Return: pointer to destination buffer
 */
char *str_cat(char *dest, char *src)
{
	char *cat = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (cat);
}
/**
*str_cpy - copyies from src to dest
*@dest: destination of string
*@src: source of string
*Return: pointer to destination
*/
char *str_cpy(char *dest, const char *src)
{
	char *point = dest;

	while (*src)
	{
		*point = *src;
		point++;
		src++;
	}
	*point = '\0';
	return (dest);
}
