#include "shell.h"

/**
 *env_ - show current environment
 * @para: Struct contain parameter.
 * Return: Always 0 on success
 */
int env_(para_t *para)
{
	printliststr(para->env);
	return (0);
}

/**
 * getenv_ - find value of an environ variable
 * @para: Struct contain parameter
 * @name: env variable name
 *
 * Return: the value of var
 */
char *getenv_(para_t *para, const char *name)
{
	catalog_t *node = para->env;
	char *po;

	while (node)
	{
		po = startswith(node->str, name);
		if (po && *po)
			return (po);
		node = node->next;
	}
	return (NULL);
}

/**
 *setenv_ - Init a new environment variable,
 *@para: Struct contain parameter.
 *  Return: Always 0 on success
 */
int setenv_(para_t *para)
{
	if (para->argc != 3)
	{
		e_puts("Incorrect number of arguements\n");
		return (1);
	}
	if (setenv__(para, para->argv[1], para->argv[2]))
		return (0);
	return (1);
}

/**
 *unsetenv_ - Remove an environment variable
 *@para: Struct contain parameter.
 *  Return: Always 0 on success
 */
int unsetenv_(para_t *para)
{
	int j;

	if (para->argc == 1)
	{
		e_puts("few arguements.\n");
		return (1);
	}
	for (j = 1; j <= para->argc; j++)
		unsetenv__(para, para->argv[j]);

	return (0);
}
/**
 *help_ - changes  the process page
 *@para: Structs contain parameter.
 *Return: Always 0 on success
 */
int help_(para_t *para)
{
	char **args;

	args = para->argv;
	put_s("help\n");
	if (0)
		put_s(*args);
	return (0);
}
