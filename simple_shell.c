#include "shell.h"
/**
 * main - entry point
 * @av: argument variable
 * @ac: argument count
 * Return: 0 on success, otherway 1
 */
int main(int ac, char **av)
{
	para_t para[] = { NULL_INIT };
	int f_d = 2;
	int j = 0;
	char *key;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (f_d)
		: "r" (f_d));

	if (ac == 2)
	{
		f_d = open(av[1], O_RDONLY);
		if (f_d == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				e_puts(av[0]);
				e_puts(": 0: Can't open ");
				e_puts(av[1]);
				e_putchar('\n');
				e_putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		para->read_fd = f_d;
	}
	env_list(para);
	sh(para, av);
	return (EXIT_SUCCESS);
}
