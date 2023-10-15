#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
char *_getenv(const char *env_var);
char *get_command(char *command);
char **split_string(char *buffer, char *del);
void _exit_shell(void);
void _print_env(void);

char **toknize(char *buffer, char *del);
char *fetch_command(char *command);
char *_getenviron(const char *_env);
void is_command_found(char *token);
void shell_print(const char *text);
void prompt_message(void);
void read_command(char *command);
void _exit_shell(void);
void _print_env(void);
#endif
