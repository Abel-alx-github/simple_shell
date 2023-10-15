#include "shell.h"
void is_command_found(char *token)
{
	if (access(token, F_OK) == 0)
		printf("%s: found", token);
	else
		printf("%s: not found", token);
}
