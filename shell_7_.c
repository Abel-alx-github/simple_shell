#include "shell.h"
 /**
  *b_free - frees allocated memory
  *@po: address of the pointer to free
  *Return: 1 if freed, otherwise 0.
  */
int b_free(void **po)
{
	if (po && *po)
	{
		free(*po);
		*po = NULL;
		return (1);
	}
	return (0);
}
/**
 *strn_cpy - copy a string
 *@dest: destination string to be copied to
 *@src: source string
 *@n: number of characters to be copied
 *Return: concatenated string
 */
char *strn_cpy(char *dest, char *src, int n)
{
	int i, j;
	char *sea = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (sea);
}

/**
 *strn_cat - concatenates two strings
 *@dest: first string
 *@src: second string
 *@n: amount of bytes to be  used
 *Return: concatenated string
 */
char *strn_cat(char *dest, char *src, int n)
{
	int i, j;
	char *sea = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (sea);
}

