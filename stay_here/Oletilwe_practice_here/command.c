#include "shell.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64

/**
* read_input - reads user input
* @input: input value
*/

void read_input(char *input)
	{
		ssize_t bytes_read;

		write(STDOUT_FILENO, "> ", 2);
		bytes_read = read(STDIN_FILENO, input, MAX_INPUT_SIZE);
		if (bytes_read > 0 && input[bytes_read - 1] == '\n')
		{
			input[bytes_read - 1] = '\0';
		}
		else
		{
			input[bytes_read] = '\0';
		}
	}
/**
* execute_command - it executes a command
* @input: input value
*/

void execute_command(char *input)
	{
		pid_t pid;
		char *args[MAX_ARGS];
		char *token = strtok(input, " ");
		int i = 0;

		while (token != NULL)
		{
			args[i++] = token;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
		}
		else if (pid == 0)
		{
			if (execvp(args[0], args) == -1)
			{
				perror("execvp");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(NULL);
		}
	}
/**
* command_execute - to handle a path
* @input: input value
* Return: always 0
*/
int command_execute(char *input)
{
	pid_t pid;
	char *args[MAX_ARGS];

	parse_arguments(input, args);
	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	} else if (pid == 0)
	{
		execute_child_process(args);
	} else
	{
		wait_and_check_status(pid, args);
	}
	return (0);
}

/**
* parse_arguments - parsing an argument
* @input: input value
* @args: arguments
*/
void parse_arguments(char *input, char **args)
{
	char *token = strtok(input, " ");
	int i = 0;

	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
}
/**
* execute_child_process - child processor
* @args: arguments
*/
void execute_child_process(char **args)
{
	if (execvp(args[0], args) == -1)
	{
		perror("execvp");
		exit(EXIT_FAILURE);
	}
}
