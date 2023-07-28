#include <stdlib.h>
#include <stdio.h>

/**
 * _realloc - Adjusts size of a memory block via malloc
 * @ptr: initial memory block
 * @old_size: byte size of initial block
 * @new_size: byte size of desired block
 *
 * Return: Pointer to resized block
 */
char **_realloc(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newPtr = NULL;
	unsigned int num, i;

	/* Check if ptr is NULL and if so, allocate new_size memory and return */
	if (!ptr)
	{
		free(ptr);
		return (malloc(sizeof(*ptr) * new_size));
	}

	/* If new_size is 0, free ptr and return NULL */
	else if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	/* If new_size equals old_size, return ptr without any modification */
	if (new_size == old_size)
		return (ptr);

	/* Assign the smaller size between new_size and old_size to num */
	num = old_size < new_size ? old_size : new_size;

	newPtr = malloc(8 * new_size);

	/* If malloc succeeds, fill newPtr and copy num elements from ptr */
	if (newPtr)
	{
		for (i = 0; i < new_size; i++)
			newPtr[i] = NULL;

		/* Copy the first num elements from ptr to newPtr */
		for (i = 0; i < num; i++)
			newPtr[i] = ptr[i];

		free(ptr);
	}

	return (newPtr);
}

