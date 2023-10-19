#include "shell.h"

/**
 * f_free - to free a pointer of pointer
 *@ptrp: pointer of pointer
 */
void f_free(char **ptrp)
{
	char **a = ptrp;

	if (!ptrp)
		return;
	while (*ptrp)
		free(*ptrp++);
	free(a);
}

/**
 *re_alloc - re_allocates memory
 * @po: pointer to previous malloc'ated
 * @oldsize: size of previous block
 * @newsize: size of new memory
 *Return: pointer to daol'block.
 */
void *re_alloc(void *po, unsigned int oldsize, unsigned int newsize)
{
	char *p;

	if (!po)
		return (malloc(newsize));
	if (!newsize)
		return (free(po), NULL);
	if (newsize == oldsize)
		return (po);

	p = malloc(newsize);
	if (!p)
		return (NULL);

	oldsize = oldsize < newsize ? oldsize : newsize;
	while (oldsize--)
		p[oldsize] = ((char *)po)[oldsize];
	free(po);
	return (p);
}
