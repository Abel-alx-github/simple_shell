#include "shell.h"
/**
 *sigintHandler_ - hundle ctrl-C
 * @sig_num: signal number
 * Return: void
 */
void sigintHandler_(__attribute__((unused))int sig_num)
{
	put_s("\n");
	put_s("$ ");
	putcha_r(BUF_FLUSH);
}
/**
 *clear_para - init para_t struct
 * @para: structuctur address
 */
void clear_para(para_t *para)
{
	para->arg = NULL;
	para->argv = NULL;
	para->path = NULL;
	para->argc = 0;
}

/**
 *set_para - init para_t structs
 *@para: struct address
 * @av: argument variable
 */
void set_para(para_t *para, char **av)
{
	int j = 0;

	para->filename = av[0];
	if (para->arg)
	{
		para->argv = str_tow(para->arg, " \t");
		if (!para->argv)
		{

			para->argv = malloc(sizeof(char *) * 2);
			if (para->argv)
			{
				para->argv[0] = str_dup(para->arg);
				para->argv[1] = NULL;
			}
		}
		for (j = 0; para->argv && para->argv[j]; j++)
		para->argc = j;
		replacealias(para);
		replacevars(para);
	}
}

/**
 * free_para - func to frees para_t structure
 * @para: structs
 * @all: true if freeing all fields
 */
void free_para(para_t *para, int all)
{
	f_free(para->argv);
	para->argv = NULL;
	para->path = NULL;
	if (all)
	{
		if (!para->cmdbuf)
			free(para->arg);
		if (para->env)
			freelist(&(para->env));
		if (para->history)
			freelist(&(para->history));
		if (para->alias)
			freelist(&(para->alias));
		f_free(para->environ);
			para->environ = NULL;
		b_free((void **)para->cmdbuf);
		if (para->read_fd > 2)
			close(para->read_fd);
		putcha_r(BUF_FLUSH);
	}
}
