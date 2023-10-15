#include "shell.h"
char *get_env(const char *envvar)
{
	extern char **environ;
	int j;
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

char *fetch_command(char *command)
{
	char *path = get_env("PATH");
	char *token;
	char *full_path;
	struct stat st;

	token = strtok(path, ":");

	while (token)
	{
		full_path = malloc(str_len(token) + str_len(command) + 2);
		str_cpy(full_path, token);
		str_cat(full_path, "/");
		str_cat(full_path, command);
		if (stat(full_path, &st) == 0)
			return (full_path);
		free(full_path);
		token = strtok(NULL, ":");
	}
	return (NULL);
}

char **toknize(char *input, char *delimter)
{
	char **all_tokens;
	char *token;
	int i = 0;

	all_tokens = malloc(sizeof(char *) * 1024);
	token = strtok(input, delimter);

	while (token)
	{
		all_tokens[i] = token;
		token = strtok(NULL, delimter);
		i++;
	}
	all_tokens[i] =  NULL;
	return (all_tokens);
}

void _exit_shell(void)
{
	write(1, "Goodbye!..man...\n", 18);
	exit(EXIT_SUCCESS);
}

void _print_env(void)
{
	extern char **environ;
	int j;

	for (j = 0; environ[j] != NULL; j++)
		printf("%s\n", environ[j]);
}

