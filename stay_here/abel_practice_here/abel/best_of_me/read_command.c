#include "shell.h"
void read_command(char *input, size_t input_size)
{
	ssize_t if_getline_fail;
	
	if_getline_fail = getline(&input, &input_size, stdin);
		if (if_getline_fail == -1)
		{
			if (feof(stdin))
			{
				printf("End of stream reached\n");
				exit(EXIT_SUCCESS);
			}
			else if (if_getline_fail == EINVAL || if_getline_fail == ENOMEM)
			{
				perror("getline");
				exit(EXIT_FAILURE);
			}
			else
			{
				fprintf(stderr, "Unexpected error: %lu\n", if_getline_fail);
			}
			exit(EXIT_FAILURE);
		}
	input[strcspn(input, "\n")] = '\0';
}
