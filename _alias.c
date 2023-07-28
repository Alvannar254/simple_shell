#include <stdlib.h>
#include "shell.h"
#include "main.h"
#include "lists.h"

/**
 * _alias - Manages shell aliases.
 * @params: Contains shell's state and command line arguments.
 *
 * Prints all aliases when no arguments are passed.
 * Otherwise, treats each argument as an alias name or definition
 * and performs the suitable operation.
 */
void _alias(param_t *params)
{
	unsigned int i;

	if (params->tokCount == 1)
	{
		/* Print existing aliases when no arguments are passed. */
		print_all_aliases(params);
		return;
	}
	/* Loop over the arguments, checking for aliases to set or print. */
	for (i = 1; i < params->tokCount; i++)
	{
		if (_strchr(params->args[i], '='))
			set_alias(params->args[i], params);
		else
			print_alias(params->args[i], params);
	}
}

/**
 * set_alias - Defines a new alias or modifies an existing one.
 * @name: The identifier of the alias to set.
 * @params: Holds the shell state.
 *
 * An alias is a shorthand for a command or group of commands.
 * This function adds or updates an alias in the shell's list of aliases.
 */
void set_alias(char *name, param_t *params)
{
	char *val, *tmp = NULL;
	unsigned int i = 0, j = 1;

	/* Identify the equal sign separating the name and value of the alias. */
	while (name[i] && name[i] != '=')
		i++;
	/* Process the alias depending on the presence of single quotes. */
	if (name[i + 1] == '\'')
	{
		/* Handle the case when alias value is enclosed in single quotes. */
		if (_strchr(&name[i + 2], '\''))
		{
			/* Process alias value and set additional alias if required. */
			tmp = _strchr(&name[i + 2], '\'');
			*tmp = '\0';
			val = _strdup(&name[i + 2]);
			/* Check for the presence of additional alias definitions. */
			if (tmp[1] != '\0')
			{
				while (tmp[j] &&
						(tmp[j] == ' ' || tmp[j] == '\t' || tmp[j] == '\n'))
					j++;
				if (tmp[j] != '\0')
					set_alias(&tmp[j], params);
			}
		}
		else
		{
			_printf("Usage: alias name='value' [...]\n");
			return;
		}
	}
	else
		val = _strdup(&name[i + 1]);
	name[i] = '\0'; /* End the name of the alias. */
	make_alias(name, val, params);
}

/**
 * make_alias - Constructs a new alias and appends it to the alias list.
 * @name: Identifier of the alias.
 * @val: Alias command.
 * @params: Contains the alias list in a struct.
 *
 * Creates a new alias with the provided name and command,
 * and adds it to the alias list. If the list is empty, the new
 * alias becomes the first node. Otherwise, it's appended to the end.
 */
void make_alias(char *name, char *val, param_t *params)
{
	list_t *h = params->alias_head;

	while (h)
	{
		/* If an alias with the same name exists, update its value. */
		if (!_strcmp(name, h->str))
		{
			free(h->val);
			h->val = val;
			h->valLen = _strlen(val);
			params->status = 0;
			return;
		}
		h = h->next;
	}
	/* Create a new alias if no existing alias is found. */

	params->alias_head = add_node(&(params->alias_head), name, val);
	free(val);
	params->status = 0;
}

