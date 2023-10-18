#include "shell.h"

/**
* prompt_message - display prompt
*/

void prompt_message(void)
{
	write(1, "shell$ ", 7);
}
