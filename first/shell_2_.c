#include "shell.h"

/**
 * unsetalias - sets alias
 * @para: parameter struct
 * @str: string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unsetalias(para_t *para, char *str)
{
	char *po, c;
	int ret;

	po = str_chr(str, '=');
	if (!po)
		return (1);
	c = *po;
	*po = 0;
	ret = deletenodeatindex(&(para->alias),
		getnodeindex(para->alias, nodestartswith(para->alias, str, -1)));
	*po = c;
	return (ret);
}

/**
 * setalias - sets alias
 * @para:structure of parametert
 * @str: string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int setalias(para_t *para, char *str)
{
	char *po;

	po = str_chr(str, '=');
	if (!po)
		return (1);
	if (!*++po)
		return (unsetalias(para, str));

	unsetalias(para, str);
	return (addnodeend(&(para->alias), str, 0) == NULL);
}

/**
 * printalias - prints alias
 * @node: an alias node
 * Return: Always 0 on success, 1 on error
 */
int printalias(catalog_t *node)
{
	char *po = NULL, *a = NULL;

	if (node)
	{
		po = str_chr(node->str, '=');
		for (a = node->str; a <= po; a++)
			putcha_r(*a);
		putcha_r('\'');
		put_s(po + 1);
		put_s("'\n");
		return (0);
	}
	return (1);
}

/**
 * alias_ - alias builtin 
 * @para: Structure containing paramet
 *  Return: Always 0 on success
 */
int alias_(para_t *para)
{
	int i = 0;
	char *po = NULL;
	catalog_t *node = NULL;

	if (para->argc == 1)
	{
		node = para->alias;
		while (node)
		{
			printalias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; para->argv[i]; i++)
	{
		po = str_chr(para->argv[i], '=');
		if (po)
			setalias(para, para->argv[i]);
		else
			printalias(nodestartswith(para->alias, para->argv[i], '='));
	}

	return (0);
}
/**
*is_interactive - if shell is interactive mode return true
*@para: structs
* Return: if interactive mode 1, 0 otherwise
 */
int is_interactive(para_t *para)
{
	return (isatty(STDIN_FILENO) && para->read_fd <= 2);
}
