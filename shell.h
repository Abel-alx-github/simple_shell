#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#define MAX_INPUT_SIZE 1024
extern char **environ;
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);

char *get_env(const char *envvar);
char *fetch_command(char *command);
char **toknize(char *input, char *delimter);
void _exit_shell(void);
void _print_env(void);
void read_command(char *input, size_t input_size);
void exec(char **args);
/**our cudtom  string.h */
int str_cmp(const char *str1, char *str2);
char *str_cat(char *dest, char *src);
char *str_cpy(char *dest, const char *src);
int str_len(char *str);


void shell_print(const char *text);
void prompt_message(void);
#endif
