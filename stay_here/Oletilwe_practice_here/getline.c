#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX_INPUT_SIZE 1024

static char buffer[MAX_INPUT_SIZE];
static int buffer_position;
static int buffer_size;

/**
* custom_getline - writes an getline function
* Return: always 0
*/
char *custom_getline()
{
	char *line = malloc(MAX_INPUT_SIZE * sizeof(char));
	int position = 0;
	char current_char;

	while (1)
	{
		if (buffer_position >= buffer_size)
		{
			buffer_size = read(STDIN_FILENO, buffer, MAX_INPUT_SIZE);
			buffer_position = 0;
			if (buffer_size == 0)
			{
				break;
			}
		}

		current_char = buffer[buffer_position++];

		if (current_char == '\n' || current_char == EOF)
		{
			line[position] = '\0';
			break;
		}
		{
		line[position++] = current_char;
		}
	}
	if (position == 0 && buffer_size == 0)
	{
		free(line);
		line = NULL;
	}
	return (line);
}
