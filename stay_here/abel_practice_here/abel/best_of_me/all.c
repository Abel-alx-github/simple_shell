#include "shell.h"
/**
*main - entry point
*
*Return: 0 on success
*/
int main(void)
{
        char *input = NULL, **args = NULL;
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
                if (input[0] == '\0')
                        continue;
                args = toknize(input, " \t\n");
                if (str_cmp(args[0], "exit") == 0)
                        _exit_shell();
                if (str_cmp(args[0], "env") == 0)
                {
                        _print_env();
                        continue;
                }
                exec(args);
		free(args);
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
extern  char **environ;
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
        char *path = NULL;
        char *token;
        char *full_path;
        struct stat st;

        if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR))
        {
                return (command);
        }
	path = get_env("PATH");
	if (path == NULL) {
    return NULL;
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

        cmd = fetch_command(*args);

        if (cmd == NULL)
        {
                write(1, "command not founddd\n", 20);
                return;
        }
        child_pid = fork();
        if (child_pid == -1)
        {
                perror("fork");
                exit(EXIT_FAILURE);
        }
        if (child_pid == 0)
        {
                if (cmd)
                {
                        execve(cmd, args, NULL);
                        perror("execve");
                        exit(EXIT_FAILURE);
                }
        }
        else
                wait(NULL);
}


/**
*toknize - it toknize input
*@delimter: limit where tokines stop
*@input: input commad from user
*Return: pointer to command
*
*/
char **toknize(char *input, char *delimter)
{
        char **all_tokens = NULL;
        char *token;
        int i = 0;

        all_tokens = malloc(sizeof(**all_tokens) * 1024);
        if (all_tokens == NULL)
                return (NULL);
        token = strtok(input, delimter);

        while (token)
        {
                if (i >= 1000)
                {
                        all_tokens = realloc(all_tokens, sizeof(char *) * (i + 1000));
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
/**
* prompt_message - display prompt
*/

void prompt_message(void)
{
        write(1, "shell$ ", 7);
}

/**
* custom_getline - reads a line of an input stream
* @lineptr: memory leak
* @n: input value
* @stream: input value
* Return: always 0
*/
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
        char *buffer = malloc(MAX_INPUT_SIZE * sizeof(char));
        int position = 0;
        int num_chars_read = 0;

        while (1)
        {
        char current_char = fgetc(stream);

        if (current_char == EOF || current_char == '\n')
        {
        break;
        }

        buffer[position++] = current_char;
        num_chars_read++;
        }

        buffer[position] = '\0';
        *lineptr = buffer;
        *n = num_chars_read;

        return (num_chars_read);
}

/**
 *str_len - returns the length of characters
 *@str: the string to count
 *
 * Return: length of string
 */
int str_len(char *str)
{
        int i = 0;

        if (!str)
                return (0);

        while (*str++)
                i++;
        return (i);
}
/**
 *str_cmp - performs lexicogarphic comparison of two strangs.
 * @str1: first strang
 * @str2: second strang
 *
 * Return: negative if str1 < str2, positive if str1 > str2, 0 if str1 == str2
 */
int str_cmp(const char *str1, char *str2)
{
        while (*str1 && *str2)
        {
                if (*str1 != *str2)
                        return (*str1 - *str2);
                str1++;
                str2++;
        }
        if (*str1 == *str2)
                return (0);
        else
                return (*str1 < *str2 ? -1 : 1);
}
/**
 *str_cat - concatenates two strings
 * @dest: the destination pointer
 * @src: the source pointer
 *
 * Return: pointer to destination buffer
 */
char *str_cat(char *dest, char *src)
{
        char *cat = dest;

        while (*dest)
                dest++;
        while (*src)
                *dest++ = *src++;
        *dest = *src;
        return (cat);
}
/**
*str_cpy - copyies from src to dest
*@dest: destination of string
*@src: source of string
*Return: pointer to destination
*/
char *str_cpy(char *dest, const char *src)
{
        char *point = dest;

        while (*src)
        {
                *point = *src;
                point++;
                src++;
        }
        *point = '\0';
        return (dest);
}
