#include "shell.h"

/**
 *sh - shell loop
 * @para: parameter & return para struct
 * @av: arg vector
 * Return: 0 on success,otherwise 1
 */
int sh(para_t *para, char **av)
{
	ssize_t ret = 0;
	int builtinret = 0;

	while (ret != -1 && builtinret != -2)
	{
		clear_para(para);
		if (is_interactive(para))
			put_s("SHELL$ ");
		e_putchar(BUF_FLUSH);
		ret = getinput(para);
		if (ret != -1)
		{
			set_para(para, av);
			builtinret = findbuiltin(para);
			if (builtinret == -1)
				findcmd(para);
		}
		else if (is_interactive(para))
			putcha_r('\n');
		free_para(para, 0);
	}
	writehistory(para);
	free_para(para, 1);
	if (!is_interactive(para) && para->status)
		exit(para->status);
	if (builtinret == -2)
	{
		if (para->errornum == -1)
			exit(para->status);
		exit(para->errornum);
	}
	return (builtinret);
}

/**
 *findbuiltin - searches a builtin command
 *@para: parameter & return para struct
 *Return:  if builtin not found -1,
 *if builtin executed successfully 0,
 *if builtin found but not successful 1,
 *if builtin signals exit() -2
 */
int findbuiltin(para_t *para)
{
	int i, builtinret = -1;
	builtintable built_intbl[] = {
		{"exit", exit_},
		{"env", env_},
		{"help", help_},
		{"history", history_},
		{"setenv", setenv_},
		{"unsetenv", unsetenv_},
		{"cd", cd_},
		{"alias", alias_},
		{NULL, NULL}
	};

	for (i = 0; built_intbl[i].type; i++)
		if (str_cmp(para->argv[0], built_intbl[i].type) == 0)
		{
			para->linecount++;
			builtinret = built_intbl[i].func(para);
			break;
		}
	return (builtinret);
}

/**
 *findcmd - search command in PATH
 *@para: parameter & return para struct
 *Return: nothing
 */
void findcmd(para_t *para)
{
	char *path = NULL;
	int i, m;

	para->path = para->argv[0];
	if (para->linecountflag == 1)
	{
		para->linecount++;
		para->linecountflag = 0;
	}
	for (i = 0, m = 0; para->arg[i]; i++)
		if (!isdelimter(para->arg[i], " \t\n"))
			m++;
	if (!m)
		return;

	path = findpath(para, getenv_(para, "PATH="), para->argv[0]);
	if (path)
	{
		para->path = path;
		forkcmd(para);
	}
	else
	{
		if ((is_interactive(para) || getenv_(para, "PATH=")
			|| para->argv[0][0] == '/') && iscmd(para, para->argv[0]))
			forkcmd(para);
		else if (*(para->arg) != '\n')
		{
			para->status = 127;
			printerror(para, "not found\n");
		}
	}
}

/**
 * forkcmd - exexute by forks to run cmd
 *@para: parameter struct
 *Return: nothing
 */
void forkcmd(para_t *para)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(para->path, para->argv, getenviron_(para)) == -1)
		{
			free_para(para, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(para->status));
		if (WIFEXITED(para->status))
		{
			para->status = WEXITSTATUS(para->status);
			if (para->status == 126)
				printerror(para, "Permission is denied\n");
		}
	}
}
/**
 *mem_set - writes on  memory with a constant byte
 *@str: pointer to the memory area
 *@byt: byte to write *str with
 *@n: of bytes to be filled
 *Return: srt a pointer to the memory area s
 */
char *mem_set(char *str, char byt, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		str[i] = byt;
	return (str);
}
