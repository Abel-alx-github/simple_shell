#include "shell.h"
void _exit_shell(void)
{
	write(STDOUT_FILENO,"Goodbye!\n", 11);
	exit(EXIT_SUCCESS);
}

void _print_env(void)
{
	extern char **environ;
	for (int i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
}
