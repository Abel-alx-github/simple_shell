#include "shell.h"

int main(int ac, char **av, char **env)
{
	char *buffer = NULL;
	char *cmd;
	char **args;	
	int status, n_chars;
	size_t buffer_size = 0;
//	ssize_t chars = 0;
	pid_t child_pid;
	while(1)
	{
		printf("$ ");	
		//read_command(buffer);
		n_chars = getline(&buffer, &buffer_size, stdin);
			if (n_chars == -1)
			{
				write(1, "\n", 1);
				exit(1);

			}
		  buffer[strcspn(buffer, "\n")] = '\0';

    			if (buffer[0] == '\0') {
  				 continue;
    			}
			args = split_string(buffer, " \t\n");
		if (strcmp(args[0], "exit") == 0)
			_exit_shell();
		if (strcmp(args[0], "env") == 0)
			_print_env();
		
		child_pid = fork();
			
			if (child_pid == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			if (child_pid == 0)
			{
				cmd = get_command(args[0]);
				if (cmd)
				{
					execve(cmd, args, env);
					perror("execve");
					exit(EXIT_FAILURE);
				}
				else
					printf("command not command\n");
				exit(0);
			}	
			else
				wait(NULL);
	}
	return 0;
}

char *_getenv(const char *env_var)
{
        extern char **environ;
        int i = 0;
        char *key;
        while (environ[i])
        {
                 key = strtok(environ[i], "=");
                 if (strcmp(env_var, key) == 0)
                       return (strtok(NULL, "\n"));
                 i++;

        }
        return (NULL);
}
char *get_command(char *command)
{
        char *path = _getenv("PATH");
        char *token ;
        char *cmd_path;
        struct stat st;

	token = strtok(path, ":");
        while(token)
        {
                cmd_path = malloc(strlen(token) + strlen(command) + 2);
               strcpy(cmd_path, token);
                strcat(cmd_path, "/");
                strcat(cmd_path, command);
               if (stat(cmd_path, &st) == 0)
                       return (cmd_path);
               free(cmd_path);
      //         token =NULL;
	       token = strtok(NULL, ":");
        }
        return (NULL);
}
char **split_string(char *buffer, char *del)
{
        char **tokens;
        char *token;
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
void _exit_shell(void)
{
	printf("Goodbye!\n");
	exit(EXIT_SUCCESS);
}
void _print_env(void)
{
        extern char **environ;
	int i;
	for (i = 0; environ[i] != NULL; i++)
                printf("%s\n", environ[i]);
}
