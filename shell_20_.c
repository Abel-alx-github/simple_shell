#include "shell.h"

/**
 *ischain -check if a char in buffer is a chain delimeter
 * @p: address of current position in buf
 *@para: parameter
 * @bufer: buffer
 * * Return: 1 if chain delimeter, 0 otherwise
 */
int ischain(para_t *para, char *bufer, size_t *p)
{
	size_t i = *p;

	if (bufer[i] == '|' && bufer[i + 1] == '|')
	{
		bufer[i] = 0;
		i++;
		para->cmdbuftype = CMD_OR;
	}
	else if (bufer[i] == '&' && bufer[i + 1] == '&')
	{
		bufer[i] = 0;
		i++;
		para->cmdbuftype = CMD_AND;
	}
	else if (bufer[i] == ';')
	{
		bufer[i] = 0;
		para->cmdbuftype = CMD_CHAIN;
	}
	else
		return (0);
	*p = i;
	return (1);
}

/**
 *checkchain - checks to continue chaining based on last status
 * @para: parameter
 * @bufer: buffer
 * @p: address of current position in buf
 * @len: length of buf
 * @i: starting position in buf
 * Return: nothing
 */
void checkchain(para_t *para, char *bufer, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (para->cmdbuftype == CMD_AND)
	{
		if (para->status)
		{
			bufer[i] = 0;
			j = len;
		}
	}
	if (para->cmdbuftype == CMD_OR)
	{
		if (!para->status)
		{
			bufer[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replacealias - replaces an aliases in the tokenized string
 * @para: parametet
 *Return: one if replaced, or zero otherwise
 */
int replacealias(para_t *para)
{
	int i;
	catalog_t *node;
	char *po;

	for (i = 0; i < 10; i++)
	{
		node = nodestartswith(para->alias, para->argv[0], '=');
		if (!node)
			return (0);
		free(para->argv[0]);
		po = str_chr(node->str, '=');
		if (!po)
			return (0);
		po = str_dup(po + 1);
		if (!po)
			return (0);
		para->argv[0] = po;
	}
	return (1);
}

/**
 * replacevars - replaces vars in the tokenized string
 * @para: parameter
 * Return: 1 if replaced, 0 otherwise
 */
int replacevars(para_t *para)
{
	int i = 0;
	catalog_t *node;

	for (i = 0; para->argv[i]; i++)
	{
		if (para->argv[i][0] != '$' || !para->argv[i][1])
			continue;

		if (!str_cmp(para->argv[i], "$?"))
		{
			replacestring(&(para->argv[i]),
				str_dup(convertnumber(para->status, 10, 0)));
			continue;
		}
		if (!str_cmp(para->argv[i], "$$"))
		{
			replacestring(&(para->argv[i]),
				str_dup(convertnumber(getpid(), 10, 0)));
			continue;
		}
		node = nodestartswith(para->env, &para->argv[i][1], '=');
		if (node)
		{
			replacestring(&(para->argv[i]),
				str_dup(str_chr(node->str, '=') + 1));
			continue;
		}
		replacestring(&para->argv[i], str_dup(""));

	}
	return (0);
}

/**
 * replacestring - replaces str
 * @oldstr: address of oldstring
 * @newstr: string
 *Return: if replaced one, otherwisezero
 */
int replacestring(char **oldstr, char *newstr)
{
	free(*oldstr);
	*oldstr = newstr;
	return (1);
}
