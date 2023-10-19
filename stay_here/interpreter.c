#include "shell.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 100

/**
* interpreter - a function that interprets a line
* Return: always 0
*/
int interpreter(void)
{
char input[MAX_INPUT_LENGTH];
pid_t pid;
int status;
	while (1)
	{
	write(STDOUT_FILENO, "$ ", 2);
	if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL)
	{
		if (feof(stdin))
		{
			printf("\n");
			break;
		}
		else
		{
			perror("reading input error");
			exit(EXIT_FAILURE);
		}
	}
	input[strlen(input) - 1] = '\0';
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		char *args[] = {input, NULL};

		execve(input, args, environ);
		perror("command not found");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			fprintf(stderr, "command exited %d\n", WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status))
		{
			fprintf(stderr, "command terminated %d\n", WTERMSIG(status));
		}
	}
	}
	return (0);
}
