#include "shell.h"

/**
 *renumberhistory - history linked list after changes
 *@para: parameter
 *Return: anew histcount
 */
int renumberhistory(para_t *para)
{
	catalog_t *node = para->history;
	int j = 0;

	while (node)
	{
		node->num = j++;
		node = node->next;
	}
	return (para->histcount = j);
}
/**
 * iscmd - to konw if a file is an executable command
 * @para: parameter struct
 * @path: path to the file
 *Return: 1 if true, 0 otherwise
 */
int iscmd(para_t *para, char *path)
{
	struct stat st;

	(void)para;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 *dupchars - duplicates chara
 * @path_str: PATH string
 * @stop: stopping index
 * @start: starting index
 * Return: pointer to  buffer
 */
char *dupchars(char *path_str, int start, int stop)
{
	static char bufer[1024];
	int i = 0, m = 0;

	for (m = 0, i = start; i < stop; i++)
		if (path_str[i] != ':')
			bufer[m++] = path_str[i];
	bufer[m] = 0;
	return (bufer);
}

/**
 * findpath - searches cmd in the PATH string
 *@para: parmetr struct
 * @path_str: PATH string
 * @cmd: cmd to search
 *Return: fullpath of cmd if found or NULL
 */
char *findpath(para_t *para, char *path_str, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!path_str)
		return (NULL);
	if ((str_len(cmd) > 2) && startswith(cmd, "./"))
	{
		if (iscmd(para, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!path_str[i] || path_str[i] == ':')
		{
			path = dupchars(path_str, curr_pos, i);
			if (!*path)
				str_cat(path, cmd);
			else
			{
				str_cat(path, "/");
				str_cat(path, cmd);
			}
			if (iscmd(para, path))
				return (path);
			if (!path_str[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
