#include "shell.h"
void exec(char **args)
{
	char *cmd;
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child_pid == 0)
	{
		cmd = fetch_command(args[0]);
		if (cmd)
		{
			execve(cmd, args, NULL);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
			write(1, "command not command\n", 20);
		exit(0);
	}
	else
		wait(NULL);
}
