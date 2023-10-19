#include "shell.h"
/**
*env_list - env linked list
*@para: Struct contain parameter.
* Return: Always 0 on success
*/
int env_list(para_t *para)
{
	catalog_t *node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		addnodeend(&node, environ[j], 0);
	para->env = node;
	return (0);
}
/**
 *exit_ - exits from shell
 *@para: Struct contains parametere.
 * Return: exits with e xit status
 */
int exit_(para_t *para)
{
	int exit_check;

	if (para->argv[1])
	{
		exit_check = erra_toi(para->argv[1]);
		if (exit_check == -1)
		{
			para->status = 2;
			printerror(para, "Illegal No: ");
			e_puts(para->argv[1]);
			e_putchar('\n');
			return (1);
		}
		para->errornum = erra_toi(para->argv[1]);
		return (-2);
	}
	para->errornum = -1;
	return (-2);
}

/**
 *cd_ - change directory of the process
 *@para: Structs contain parameter.
 *  Return: Always 0 on success
 */
int cd_(para_t *para)
{
	char *str, *dir, buffer[1024];
	int chdir_ret;

	str = getcwd(buffer, 1024);
	if (!str)
		put_s("TODO: >>getcwd failure<<\n");
	if (!para->argv[1])
	{
		dir = getenv_(para, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = getenv_(para, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (str_cmp(para->argv[1], "-") == 0)
	{
		if (!getenv_(para, "OLDPWD="))
		{
			put_s(str);
			putcha_r('\n');
			return (1);
		}
		put_s(getenv_(para, "OLDPWD=")), putcha_r('\n');
		chdir_ret =
			chdir((dir = getenv_(para, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(para->argv[1]);
	if (chdir_ret == -1)
	{
		printerror(para, "can't cd to ");
		e_puts(para->argv[1]), e_putchar('\n');
	}
	else
	{
		setenv__(para, "OLDPWD", getenv_(para, "PWD="));
		setenv__(para, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
