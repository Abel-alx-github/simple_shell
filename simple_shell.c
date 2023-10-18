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
				write(1, "End of stream reached\n",23);
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
		{
			_print_env();
		}
		exec(args);
		free(input);
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

/**
* *fetch_command - it fetchs a command
* @command: input value
* Return: always 0
*/
char *fetch_command(char *command)
{
	char *path = get_env("PATH");
	char *token;
	char *full_path;
	struct stat st;

	if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR))
	{
		return (command);
	}
	token = strtok(path, ":");

	while (token)
	{
		full_path = malloc(str_len(token) + str_len(command) + 2);
			if (full_path == NULL)
				return (NULL);
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
*exec - function that execute if the args is executable
*@args: pointer to path of command
*
*/
void exec(char **args)
{
	char *cmd;
	pid_t child_pid;

	child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (child_pid == 0)
		{
			cmd = fetch_command(args[0]);
			if (cmd)
			{
				execve(cmd, args, NULL);
				perror("execve");
				exit(EXIT_FAILURE);
			}
			else
			{
				write(1, "command not found\n", 20);
				exit(0);
			}
		}
		else
			wait(NULL);
}
