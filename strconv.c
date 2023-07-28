#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include <stdio.h>

/**
 * process_string - Turns command into string tokens.
 * @params: Command and other related parameters.
 *
 * Description: Transforms a given command into string tokens. If an alias
 * for the command exists, it is used instead.
 *
 * Return: Returns the count of tokens, or 0 if no tokens are found.
 */
int process_string(param_t *params)
{
	char *token = NULL, *state = NULL;
	char *alias = NULL, *state_2 = NULL, *val;
	list_t *node;

	/* Convert command to tokens */
	token = _strtok(params->nextCommand, " \n\t", &state);

	/* If no tokens, return 0 */
	if (!token)
	{
		params->tokCount = 0;
		return (0);
	}

	/* Search for command alias */
	node = get_node(params->alias_head, token);

	/* If alias exists, free token and use alias */
	if (node != NULL)
	{
		free(token);
		token = NULL;
		alias = _strdup(node->val);
		/* If no alias, print error and exit */
		if (!alias)
		{
			write(STDERR_FILENO, "alias expansion malloc error\n", 18);
			free_params(params);
			exit(-1);
		}
		/* Tokenize alias */
		val = _strtok(alias, " \n\t", &state_2);
		(params->args)[(params->tokCount)++] = val;
		while (val)
		{
			val = _strtok(alias, " ", &state_2);
			(params->args)[(params->tokCount)++] = val;
		}
		free(alias);
	}
	else
	{
		/* If no alias, use original token */
		(params->args)[(params->tokCount)++] = token;
	}

	/* Continue tokenizing the command */
	token = _strtok(params->nextCommand, " \n\t", &state);
	params->args[params->tokCount++] = token;
	while (token)
	{
		token = _strtok(params->nextCommand, " \n\t", &state);
		(params->args)[(params->tokCount)++] = token;
		/* If token count reaches capacity, increase array size */
		if (params->tokCount == params->argsCap)
		{
			params->argsCap += 10;
			params->args = _realloc(params->args, params->argsCap - 10,
					params->argsCap);
			/* If realloc fails, print error and exit */
			if (!(params->args))
			{
				write(STDERR_FILENO, "realloc error\n", 14);
				free_params(params);
				exit(-1);
			}
		}
	}

	/* Return total number of tokens minus one */
	return (params->tokCount - 1);
}

