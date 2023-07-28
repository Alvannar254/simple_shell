#include <stdlib.h>
#include "shell.h"
#include "main.h"
#include "lists.h"

/**
 * _setenv - Modifies or creates an environment variable
 * @params: Struct holding parameters for the function
 */
void _setenv(param_t *params)
{
	/* Pointer for temporary operations */
	char *tmp = NULL;
	/* Extracting name and value from arguments */
	char *name = params->args[1], *value = params->args[2];
	/* Pointer to environment variables list */
	list_t *h = params->env_head;

	if (params->tokCount != 3)
	{
		params->status = 0;
		return;
	}
	while (h)
	{
		/* If environment variable found */
		if (_strcmp(name, h->str) == 0)
		{
			/* Free old value and assign new one */
			tmp = h->val;
			free(tmp);
			h->val = _strdup(value);
			if (!h->val)
			{
				/* Exit on memory allocation error */
				write(STDERR_FILENO, "setenv malloc error\n", 18);
				exit(-1);
			}
			/* Update value length and status */
			h->valLen = _strlen(value);
			params->status = 0;
			return;
		}
		h = h->next;
	}
	/* If variable not found, add new one */
	params->env_head = add_node(&(params->env_head), name, value);
	params->status = 0;
}
/**
 * _unsetenv - Removes an environment variable
 * @params: Struct holding parameters for the function
 */
void _unsetenv(param_t *params)
{
	/* Extracting name from arguments */
	char *name = params->args[1];
	/* Pointers to environment variables list */
	list_t *prev = NULL, *h = params->env_head;

	if (params->tokCount != 2)
	{
		params->status = 0;
		return;
	}
	while (h)
	{
		/* If environment variable found */
		if (_strcmp(name, h->str) == 0)
		{
			/* Adjust list links */
			if (h == params->env_head)
				params->env_head = h->next;
			else
				prev->next = h->next;

			/* Free memory and return */
			free(h->str);
			free(h->val);
			free(h);
			params->status = 0;
			return;
		}
		prev = h;
		h = h->next;
	}
	params->status = 0;
}

