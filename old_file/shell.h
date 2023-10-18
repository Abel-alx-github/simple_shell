#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#define MAX_INPUT_SIZE 1024

static char buffer[MAX_INPUT_SIZE];
static int buffer_position;
static int buffer_size;
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);

void shell_print(const char *text);
void prompt_message(void);
void team_memebers(void);
int interpreter(void);
void read_command(char cmd[], char *para[]);
int intepreter(void);
void read_stdin(char *command);
void read_input(char *input); /* this one as well */
void execute_command(char *input); /* from the code i added */
#endif
