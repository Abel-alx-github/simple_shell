#include "shell.h"
/**
*main - entry point
*
*Return: 0 on success
*/
int main(void)
{
	char *input = NULL, **args;
	size_t input_size = 0;
	ssize_t if_getline_fail;

	while (1)
	{
		prompt_message();
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
		if (input[0] == '\0')
			continue;
		args = toknize(input, " \t\n");
		if (str_cmp(args[0], "exit") == 0)
			_exit_shell();
		if (str_cmp(args[0], "env") == 0)
			_print_env();
		exec(args);
	}
	return (0);
}
