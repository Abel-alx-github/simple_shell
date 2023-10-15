#include "shell.h"
void read_command(char *command)
{
	char *token = NULL, *line = NULL;
	size_t line_size = 0;
	ssize_t if_getline_fail;
	int i = 0;
	
	if_getline_fail = getline(&command, &line_size, stdin);
		if (if_getline_fail == -1)
		{
			if (feof(stdin))
			{
				printf("End of stream reached\n");
				free(command);
				exit(EXIT_SUCCESS);
			}
			else if (if_getline_fail == EINVAL || if_getline_fail == ENOMEM)
			{
				perror("getline");
				free(command);
				exit(EXIT_FAILURE);
			}
			else
			{
				fprintf(stderr, "Unexpected error: %zd\n", if_getline_fail);
			}
			free(command);
			exit(EXIT_FAILURE);
		}
	command[strcspn(command, "\n")] = '\0';
		if (command[0] == '\0')
		return;
}
