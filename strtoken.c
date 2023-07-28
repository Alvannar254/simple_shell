#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include <stdio.h>

/**
 * handle_alias - Handles alias for a given token
 * @params: Command and other related parameters
 * @token: The current token
 *
 * Return: The token to be used (either the original or the alias)
 */
char *handle_alias(param_t *params, char *token)
{
	list_t *node;
	char *alias = NULL, *state_2 = NULL, *val;

	node = get_node(params->alias_head, token);
	if (node != NULL)
	{
		free(token);
		token = NULL;
		alias = _strdup(node->val);
		if (!alias)
		{
			write(STDERR_FILENO, "alias expansion malloc error\n", 18);
			free_params(params);
			exit(-1);
		}
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
		(params->args)[(params->tokCount)++] = token;
	}
	return (token);
}

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

	token = _strtok(params->nextCommand, " \n\t", &state);
	if (!token)
	{
		params->tokCount = 0;
		return (0);
	}

	token = handle_alias(params, token);

	token = _strtok(params->nextCommand, " \n\t", &state);
	params->args[params->tokCount++] = token;
	while (token)
	{
		token = _strtok(params->nextCommand, " \n\t", &state);
		(params->args)[(params->tokCount)++] = token;
		if (params->tokCount == params->argsCap)
		{
			params->argsCap += 10;
			params->args = _realloc(params->args, params->argsCap - 10,
					params->argsCap);
			if (!(params->args))
			{
				write(STDERR_FILENO, "realloc error\n", 14);
				free_params(params);
				exit(-1);
			}
		}
	}

	return (params->tokCount - 1);
}

