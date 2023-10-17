#include "shell.h"

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

	if (!buffer)
	{
		return (-1);
	}
	int position = 0;
	int current_char;

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
