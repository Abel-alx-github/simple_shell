#include "shell.h"
/**
*read_command - reads command line, tokenize and
*store the first command in cmd
*and the rest arguments are stored as
*parameter in array pointer para
*@cmd: store the first command
*@para: store parameters(arguments) pass to command
*Return: nothing
*/

void read_command(char cmd[], char *para[])
{
	char *line;
	int i = 0, j = 0;
	char *array[100], *token;
	ssize_t if_fail;
	size_t size = 0;

	if_fail = getline(&line, &size, stdin);
		if (if_fail == -1)
		{
			perror("getline failed");
			free(line);
			exit(EXIT_FAILURE);
		}
	//	if (size == 0)
	//		exit(EXIT_SUCCESS);
//		if (line1] == '\n')
//			line[size - 1] = '\0';
	line[strcspn(line, "\n")] = '\0';
  
      // If the command is empty, continue to the next iteration.
 	   if (line[0] == '\0')
	   {
	       return;
	    }
		token = strtok(line, " \n");

		while (token != NULL)
		{
			array[i++] = strdup(token);
			token = strtok(NULL, " \n");
		}
		strcpy(cmd, array[0]);
		for (j = 0; j < i; j++)
		{
			para[j] = array[j];
		}
		para[i] = NULL;
		free(line);
}
