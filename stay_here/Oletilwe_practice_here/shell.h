#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
void shell_print(const char *text);
void prompt_message(void);
void team_memebers(void);
int interpreter(void);
void read_command(char cmd[], char *para[]);
int intepreter(void);
void read_stdin(char *command);
void read_input(char *input);
void execute_command(char *input);
int command_execute(char *input);
ssize_t arguments(char **lineptr, size_t *n, FILE *stream);
void parse_arguments(char *input, char **args);
void execute_child_process(char **args);
void wait_and_check_status(pid_t pid, char **args);
void handle_command_not_found(char *command);
#endif
