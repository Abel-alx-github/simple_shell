#include "shell.h"

/**
*read_stdin - function that read input(command) from stdin.
*@command: input from stdin
*Return: nothing.
*
*/

void read_stdin(char *command)
{
	ssize_t len = 0;
	size_t size;

	len = getline(&command, &size, stdin);
		if (len == -1)
			exit(EXIT_FAILURE);
}
