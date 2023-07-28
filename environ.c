#include "main.h" /* Main program header file */
#include "lists.h" /* Header for linked list operations */
#include "shell.h" /* Shell operations header file */
#include <stdlib.h> /* Standard library header file */

/**
 * _getenv - Fetches the value of a particular environment variable.
 * @name: Identifies the environment variable of interest.
 * @params: Points to the structure containing the list.
 *
 * Return: Pointer to the desired environment variable's value, or NUL.
 *
 * This function combs through the variable linked list housed in the
 * parameter structure, looking for a variable 'name'. If a match is
 * encountered, it value is duplicated and returned as a string.
 * The function yields NULL if the sought variable is not found.
 */

char *_getenv(char *name, param_t *params)
{
	list_t *ptr = params->env_head; /* Start of environment variable list */

	/* Cycle through linked list */
	while (ptr)
	{
		/* If match found, duplicate value and return */
		if (!_strcmp(name, ptr->str))
			return (_strdup(ptr->val));

		ptr = ptr->next; /* Advance to next node */
	}
	/* If no match found, return NULL */
	return (NULL);
}

