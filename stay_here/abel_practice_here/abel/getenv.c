#include "shell.h"
char *_getenviron(const char *_env)
{
	extern char **environ;
	int i = 0;
	char *keys;
	
	while (environ[i])
	{

		keys = strtok(environ[i], "=");
		if (strcmp(_env, keys) == 0)
			return (strtok(NULL, "\n"));
		i++;

	}
	return (NULL);

}

char *fetch_command(char *command)
{
	char *path = _getenviron("PATH");
	char *token;
	char *full_path;
	struct stat st;

	token = strtok(path, ":");
	while(token)
	{
		full_path = malloc(strlen(token) + strlen(command) + 2);
		strcpy(full_path, token);
		strcat(full_path, "/");
		strcat(full_path, command);
		if (stat(full_path, &st) == 0)
			return (full_path);
		free(full_path);
		token = strtok(NULL, ":");
	}
	return (NULL);
}

char **toknize(char *buffer, char *del)
{
	char **tokens;
	char token;
	int i = 0;

	tokens = malloc(sizeof(char *) * 1024);
	token = strtok(buffer, del);
	while (token)
	{
		tokens[i] = token;
		token = strtok(NULL, del);
		i++;
	}
	tokens[i] =  NULL;
	return (tokens);
}
