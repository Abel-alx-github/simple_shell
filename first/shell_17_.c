#include "shell.h"

/**
 *str_len - returns length of str
 *@str: string thr length to check
 *Return: length of string
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
 *str_cmp - do lexicogarphic comparison of two strangs.
 * @str1: first string
 * @str2: second string
 * Return: negative(str1 < str2), positive(str1 > str2), zero str1 == str2
 */
int str_cmp(char *str1, char *str2)
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
 * startswith - look for needl starts with hay_stack
 * @hay_stack: to search
 * @needl: substring to find
 *Return: pointer of next char of haystack or NULL
 */
char *startswith(const char *hay_stack, const char *needl)
{
	while (*needl)
		if (*needl++ != *hay_stack++)
			return (NULL);
	return ((char *)hay_stack);
}

/**
 * str_cat - concatenates two strings
 * @dest: destination buffer
 * @src: source buffer
 * Return: pointer to destination buffer
 */
char *str_cat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
/**
 *str_cpy - copies a string
 *@dest:destination
 *@src: source
 *Return: pointer to destination
 */
char *str_cpy(char *dest, char *src)
{
	int j = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[j])
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = 0;
	return (dest);
}
