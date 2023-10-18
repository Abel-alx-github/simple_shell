#include "shell.h"

/**
* *fetch_command - it fetchs a command
* @command: input value
* Return: always 0
*
char *fetch_command(char *command)
{
	char *path = get_env("PATH");
	char *token;
	char *full_path;
	struct stat st;
if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR)) {
    return (command);}
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

/**
* toknize - tokenize a string based on a specific delimer
* @input: input value
* @delimter: input value
* Return: 0
*/
/*char **toknize(char *input, char *delimter)
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
}*/
char **toknize(char *input, char *delimter)
{
    char **all_tokens;
    char *token;
    int i = 0;

    all_tokens = malloc(sizeof(char *) * 16);
    if (all_tokens == NULL) {
        return NULL;
    }

    token = strtok(input, delimter);
    while (token) {
        if (i >= 16) {
            all_tokens = realloc(all_tokens, sizeof(char *) * (i + 16));
            if (all_tokens == NULL) {
                free(all_tokens);
                return NULL;
            }
        }

        all_tokens[i] = token;
        i++;
        token = strtok(NULL, delimter);
    }

    all_tokens[i] = NULL;

    return all_tokens;
}

/**
* _exit_shell - exit shell
*/
void _exit_shell(void)
{
	write(1, "Goodbye!..man...\n", 18);
	exit(EXIT_SUCCESS);
}
