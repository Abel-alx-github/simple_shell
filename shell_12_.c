#include "shell.h"

/**
 *listlen - ;ength of linked list
 *@hd: first node poiter
 *Return: size of catalog
 */
size_t listlen(const catalog_t *hd)
{
	size_t i = 0;

	while (hd)
	{
		hd = hd->next;
		i++;
	}
	return (i);
}

/**
 * listtostrings - returns strings of the list->str
 * @head: point ti  first node
 *Return: strings
 */
char **listtostrings(catalog_t *head)
{
	catalog_t *node = head;
	size_t i = listlen(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(str_len(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = str_cpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * printlist - prints all members of a catalog_t linked list
 * @hd: pointer to first node
 *
 * Return: size of list
 */
size_t printlist(const catalog_t *hd)
{
	size_t i = 0;

	while (hd)
	{
		put_s(convertnumber(hd->num, 10, 0));
		putcha_r(':');
		putcha_r(' ');
		put_s(hd->str ? hd->str : "(nil)");
		put_s("\n");
		hd = hd->next;
		i++;
	}
	return (i);
}

/**
 * nodestartswith - returns node starts with pref
 * @node: pointer to thelist head
 * @pref: string  to be simmilar
 * @c: the next chara after pref to match
 * Return: match node or null
 */
catalog_t *nodestartswith(catalog_t *node, char *pref, char c)
{
	char *po = NULL;

	while (node)
	{
		po = startswith(node->str, pref);
		if (po && ((c == -1) || (*po == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
