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
		if_getline_fail = custom_getline(&input, &input_size, stdin);
		if (if_getline_fail == -1)
		{
			if (feof(stdin))
			{
				printf("End of stream reached\n");
				exit(EXIT_SUCCESS);
			}
			else if (if_getline_fail == EINVAL || if_getline_fail == ENOMEM)
			{
				perror("custom_getline");
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

/**
* _print_env - print the current environment
*/
void _print_env(void)
{
	extern char **environ;
	int j;

	for (j = 0; environ[j] != NULL; j++)
	{
		write(STDOUT_FILENO, environ[j], str_len(environ[j]));
		write(STDOUT_FILENO, "\n", 1);
	}
}

/**
 *
 *get_env - it retrieves the value of a specific variable
 * @envvar: input value
 * Return: always 0
 */
char *get_env(const char *envvar)
{
extern	char **environ;
	int j = 0;
	char *key;

	while (environ[j])
	{
		key = strtok(environ[j], "=");
		if (str_cmp(envvar, key) == 0)
			return (strtok(NULL, "\n"));
		j++;
	}
	return (NULL);

}
