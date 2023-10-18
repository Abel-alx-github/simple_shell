#include "shell.h"

/**
*toknize - it toknize input
*@delimter: limit where tokines stop
*@input: input commad from user
*Return: pointer to command
*
*/
char **toknize(char *input, char *delimter)
{
	char **all_tokens;
	char *token;
	int i = 0;

	all_tokens = malloc(sizeof(char *) * 16);
	if (all_tokens == NULL)
		return (NULL);
	token = strtok(input, delimter);

	while (token)
	{
		if (i >= 16)
		{
			all_tokens = realloc(all_tokens, sizeof(char *) * (i + 16));
			if (all_tokens == NULL)
			{
				free(all_tokens);
				return (NULL);
			}
		}
		all_tokens[i] = token;
		i++;
		token = strtok(NULL, delimter);
	}
	all_tokens[i] = NULL;
	return (all_tokens);
}

/**
* _exit_shell - exit shell
*/
void _exit_shell(void)
{
	write(1, "Goodbye!..man...\n", 18);
	exit(EXIT_SUCCESS);
}
