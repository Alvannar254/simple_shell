#include <stdlib.h>     /* Including the standard library */
#include <unistd.h>     /* Including the unistd library */
#include <sys/wait.h>   /* Including the sys/wait library */
#include "shell.h"      /* Including the shell header file */
#include "lists.h"      /* Including the lists header file */
#include "main.h"       /* Including the main header file */

/**
 * get_builtin - Fetches built-in function
 * @params: Holds the pointer to the param_t structure with command parameters
 *
 * A brief: looks for a built-in function matching the first argument
 * in the param_t structure. If a match is found, it returns a pointer to the
 * respective built-in function, if not, it returns NULL.
 *
 * Return: Function pointer to the matching built-in function.
 */

void (*get_builtin(param_t *params))(param_t *)
{
	/* An array of operator structs with builtin functions and their names */
	op_t ops[] = {
		{"exit", _myExit},
		{"clear", _clear},
		{"env", _printenv},
		{"setenv", _setenv},
		{"cd", _cd},
		{"unsetenv", _unsetenv},
		{"alias", _alias},
		{NULL, NULL}, /* sentinel value to end the array */
	};
	op_t *op = ops; /* Pointing to the first element of the array */

	/* Loop through ops until NULL sentinel value is found */
	while (op->name)
	{
		/* name of the operation matches the first argument?, return function */
		if (!_strcmp(params->args[0], op->name))
			return (op->func);
		op++; /* Move to the next operation */
	}
	return (NULL); /* Return NULL if no matching function is found */
}

