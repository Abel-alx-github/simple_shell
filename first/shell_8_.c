#include "shell.h"
/**
*str_chr - search a character in a string
*@str: string to be parsed
*@ch: chara to search for
*Return: (str) a pointer to the memory area s
 */
char *str_chr(char *str, char ch)
{
	do {
		if (*str == ch)
			return (str);
	} while (*str++ != '\0');
	return (NULL);
}
/**
 *getenviron_ - returns environ
 * @para: Struct contain parameter.
 * Return: Always 0 on succss
 */
char **getenviron_(para_t *para)
{
	if (!para->environ || para->envchanged)
	{
		para->environ = listtostrings(para->env);
		para->envchanged = 0;
	}

	return (para->environ);
}

/**
 *unsetenv__ - Remove environment variable
 * @para: Structs contain parameter.
 *  Return: 1 on removed, 0 otherwise
 * @var: string env var property
 */
int unsetenv__(para_t *para, char *var)
{
	catalog_t *node = para->env;
	size_t j = 0;
	char *po;

	if (!node || !var)
		return (0);

	while (node)
	{
		po = startswith(node->str, var);
		if (po && *po == '=')
		{
			para->envchanged = deletenodeatindex(&(para->env), j);
			j = 0;
			node = para->env;
			continue;
		}
		node = node->next;
		j++;
	}
	return (para->envchanged);
}

/**
 *setenv__ - Init environment variable
 * @para: Structsontain parameter.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int setenv__(para_t *para, char *var, char *value)
{
	char *bufer = NULL;
	catalog_t *node;
	char *po;

	if (!var || !value)
		return (0);

	bufer = malloc(str_len(var) + str_len(value) + 2);
	if (!bufer)
		return (1);
	str_cpy(bufer, var);
	str_cat(bufer, "=");
	str_cat(bufer, value);
	node = para->env;
	while (node)
	{
		po = startswith(node->str, var);
		if (po && *po == '=')
		{
			free(node->str);
			node->str = bufer;
			para->envchanged = 1;
			return (0);
		}
		node = node->next;
	}
	addnodeend(&(para->env), bufer, 0);
	free(bufer);
	para->envchanged = 1;
	return (0);
}
