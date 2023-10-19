#include "shell.h"

/**
 *addnode - add a node beginning of the list
 * @head: pointer to head node
 * @str: field of node
 * @num: node index of history
 *Return: size of t
 */
catalog_t *addnode(catalog_t **head, const char *str, int num)
{
	catalog_t *new_hd;

	if (!head)
		return (NULL);
	new_hd = malloc(sizeof(catalog_t));
	if (!new_hd)
		return (NULL);
	mem_set((void *)new_hd, 0, sizeof(catalog_t));
	new_hd->num = num;
	if (str)
	{
		new_hd->str = str_dup(str);
		if (!new_hd->str)
		{
			free(new_hd);
			return (NULL);
		}
	}
	new_hd->next = *head;
	*head = new_hd;
	return (new_hd);
}

/**
 * addnodeend - adds a node to end of the list
 * @num: node index of history
 * @head:pointer to head node
 * @str: field of node
 * Return: size of list
 */
catalog_t *addnodeend(catalog_t **head, const char *str, int num)
{
	catalog_t *new_nod, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_nod = malloc(sizeof(catalog_t));
	if (!new_nod)
		return (NULL);
	mem_set((void *)new_nod, 0, sizeof(catalog_t));
	new_nod->num = num;
	if (str)
	{
		new_nod->str = str_dup(str);
		if (!new_nod->str)
		{
			free(new_nod);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_nod;
	}
	else
		*head = new_nod;
	return (new_nod);
}

/**
 * printliststr - writes only the str element of a catalog_t linked list
 * @hd: pointer to first node
 * * Return: size of list
 */
size_t printliststr(const catalog_t *hd)
{
	size_t i = 0;

	while (hd)
	{
		put_s(hd->str ? hd->str : "(nil)");
		put_s("\n");
		hd = hd->next;
		i++;
	}
	return (i);
}

/**
 *deletenodeatindex - remove node at given index
 * @index: index of node to delete
 * @head: pointer to first node
 * Return: 1 on success,otherways 0
 */
int deletenodeatindex(catalog_t **head, unsigned int index)
{
	catalog_t *node, *prev_nod;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_nod->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_nod = node;
		node = node->next;
	}
	return (0);
}

/**
 * freelist - frees every nodes of a list
 * @headptr: address of pointer to head node
 *Return: no value
 */
void freelist(catalog_t **headptr)
{
	catalog_t *node, *next_nod, *head;

	if (!headptr || !*headptr)
		return;
	head = *headptr;
	node = head;
	while (node)
	{
		next_nod = node->next;
		free(node->str);
		free(node);
		node = next_nod;
	}
	*headptr = NULL;
}
