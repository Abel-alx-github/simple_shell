#include "shell.h"
#define MAX_INPUT_SIZE 1024

/**
* arguments - can handle command lines with arguments
* @lineptr: memory leak
* @n: input value
* @stream: input value
* Return: always 0
*/
ssize_t arguments(char **lineptr, size_t *n, FILE *stream)
{
	size_t buffer_size = MAX_INPUT_SIZE;
	char *buffer = (char *)malloc(buffer_size * sizeof(char));
	size_t position = 0;
	int current_char;

	if (!buffer)
	{
		return (-1);
	}

	while (1)
	{
		current_char = fgetc(stream);
		if (current_char == EOF || current_char == '\n')
		{
			break;
		}
		if (position >= buffer_size - 1)
		{
			buffer_size *= 2;
			buffer = (char *)realloc(buffer, buffer_size);
			if (!buffer)
			{
				return (-1);
			}
		}
		buffer[position++] = current_char;
	}
	buffer[position] = '\0';
	*lineptr = buffer;
	*n = position;
	if (current_char == EOF && position == 0)
	{
		free(buffer);
		return (-1);
	}
	return (position);
}
/**
* wait_and_check_status - to check status
* @args: arguments
* @pid: input value
*/
void wait_and_check_status(pid_t pid, char **args)
{
	int status;

	waitpid(pid, &status, 0);

	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 127)
		{
			handle_command_not_found(args[0]);
		}
	}
}

/**
* handle_command_not_found - checking if a command not found
* @command: output value
*/
void handle_command_not_found(char *command)
{
	char error_message[100];

	sprintf(error_message, "command not found: %s\n", command);
	write(STDOUT_FILENO, error_message, strlen(error_message));
	exit(EXIT_FAILURE);
}
