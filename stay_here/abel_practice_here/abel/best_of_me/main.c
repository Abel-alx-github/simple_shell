#include "shell.h"

int main()
{
	char *input = NULL, *cmd, **args;
	size_t input_size = 0;
	ssize_t if_getline_fail = 0;
	pid_t child_pid;


	while (1)
	{
		prompt_message();
		if_getline_fail = getline(&input, &input_size, stdin);
		if (if_getline_fail == -1)
		{
			write(1, "\n", 1);
			exit(1);
		}
		input[strcspn(input, "\n")] = '\0';
		if (input[0] == '\0')
			continue;
		args = toknize(input, " \t\n");
		if (str_cmp(args[0], "exit") == 0)
			_exit_shell();
		if (str_cmp(args[0], "env") == 0)
			_print_env();
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (child_pid == 0)
		{
			cmd = fetch_command(args[0]);
			if (cmd)
			{
				execve(cmd, args, NULL);
				perror("execve");
				exit(EXIT_FAILURE);
			}
			else
				write(1, "command not command\n", 20);
			exit(0);
		}
		else
			wait(NULL);
	}
	return (0);
}
