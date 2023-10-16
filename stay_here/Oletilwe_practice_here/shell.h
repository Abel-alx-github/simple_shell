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
#endif
