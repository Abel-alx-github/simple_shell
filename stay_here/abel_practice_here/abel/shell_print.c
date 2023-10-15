#include "shell.h"
/**
* shell_print - takes a single argument
* @text: input value
*/

void shell_print(const char *text)
{
write(STDOUT_FILENO, text, strlen(text));
}
