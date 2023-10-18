#include "shell.h"
/**
*exec - function that execute if the args is executable
*@args: pointer to path of command
*
*
void exec(char **args)
{
	char *cmd;
	pid_t child_pid;

	cmd = fetch_command(args[0]);

	if (cmd == NULL)
	{
		write(1, "command not founddd\n", 20);
		exit(0);
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		if (cmd)
		{
			execve(cmd, args, NULL);
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(NULL);
}*/
