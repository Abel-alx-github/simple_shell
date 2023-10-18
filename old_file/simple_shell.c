#include "shell.h"
/**
*main - entry
*Return: 0 on success
*/
int main(void)
{
	char cmd[100], command[100], *para[20];
	char *environ[] = {(char *) "PATH=/bin", NULL};

	while (1)
	{
		prompt_message();
		read_command(command, para);
		if (fork() != 0)
		{
			wait(NULL);
		}
		else
		{
			strcpy(cmd, "/bin/");
			strcat(cmd, command);
			execve(cmd, para, environ);
		}
		if (strcmp(command, "exit") == 0)
			break;
	}
	return (0);
}
