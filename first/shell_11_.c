#include "shell.h"
/**
 *getnodeindex - find index of a node
 *@head: pointer to list head
 *@node: pointer to the node
 *eturn: index of node or -1
 */
ssize_t getnodeindex(catalog_t *head, catalog_t *node)
{
	size_t j = 0;

	while (head)
	{
		if (head == node)
			return (j);
		head = head->next;
		j++;
	}
	return (-1);
}
/**
 *gethistoryfile - history file
 * @para: parameter struct
 *Return:string containg history file
 */

char *gethistoryfile(para_t *para)
{
	char *bufer, *dir;

	dir = getenv_(para, "HOME=");
	if (!dir)
		return (NULL);
	bufer = malloc(sizeof(char) * (str_len(dir) + str_len(HIST_FILE) + 2));
	if (!bufer)
		return (NULL);
	bufer[0] = 0;
	str_cpy(bufer, dir);
	str_cat(bufer, "/");
	str_cat(bufer, HIST_FILE);
	return (bufer);
}

/**
 * writehistory - make or appends a file to an existing file
 * @para: parameter struct
 *Return: 1 on success, else -1
 */
int writehistory(para_t *para)
{
	ssize_t f_d;
	char *filename = gethistoryfile(para);
	catalog_t *node = NULL;

	if (!filename)
		return (-1);

	f_d = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (f_d == -1)
		return (-1);
	for (node = para->history; node; node = node->next)
	{
		puts_fd(node->str, f_d);
		put_fd('\n', f_d);
	}
	put_fd(BUF_FLUSH, f_d);
	close(f_d);
	return (1);
}

/**
 * readhistory - gets history from file
 * @para: parameter struct
 *Return: on success count, 0 otherwise
 */
int readhistory(para_t *para)
{
	int j, last = 0, linecount = 0;
	ssize_t f_d, rdlen, fsize = 0;
	struct stat st;
	char *bufer = NULL, *filename = gethistoryfile(para);

	if (!filename)
		return (0);

	f_d = open(filename, O_RDONLY);
	free(filename);
	if (f_d == -1)
		return (0);
	if (!fstat(f_d, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	bufer = malloc(sizeof(char) * (fsize + 1));
	if (!bufer)
		return (0);
	rdlen = read(f_d, bufer, fsize);
	bufer[fsize] = 0;
	if (rdlen <= 0)
		return (free(bufer), 0);
	close(f_d);
	for (j = 0; j < fsize; j++)
		if (bufer[j] == '\n')
		{
			bufer[j] = 0;
			buildhistorylist(para, bufer + last, linecount++);
			last = j + 1;
		}
	if (last != j)
		buildhistorylist(para, bufer + last, linecount++);
	free(bufer);
	para->histcount = linecount;
	while (para->histcount-- >= HIST_MAX)
		deletenodeatindex(&(para->history), 0);
	renumberhistory(para);
	return (para->histcount);
}

/**
 * buildhistorylist - build entry to a history list
 * @para: parapmetr
 * @linecount: history linecount, histcount
 * @bufer: buffer
 * Return: Always 0 success
 */
int buildhistorylist(para_t *para, char *bufer, int linecount)
{
	catalog_t *node = NULL;

	if (para->history)
		node = para->history;
	addnodeend(&node, bufer, linecount);

	if (!para->history)
		para->history = node;
	return (0);
}
