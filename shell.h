#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
void shell_print(const char *text);
void prompt_message(void);
void team_memebers(void);
int main (void);/* why did you add this?*/
void read_stdin(char* command);
#endif
