#define _GNU_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "shell.h"
#include "main.h" /* Import printf function implementation */
#define BUFFER_SIZE 4096
param_t *init_param(char **argv, char **env);

/**
 * main - Initializes the shell and manages the user input loop
 * @argc: Quantity of command line arguments (unused)
 * @argv: Array of command line arguments
 * @env: Environment variables array
 *
 * Return: 0 when shell exits normally
 */
int main(int __attribute__((unused)) argc, char **argv, char **env)
{
	param_t *params = NULL;
	int cond = -2, status;
	unsigned int i;
	char *state = NULL;
	size_t size = BUFFER_SIZE;

	params = init_param(argv, env); /* Initialize shell parameters */
	if (!params)
		exit(-1);
	signal(SIGINT, sigint_handler); /* Signal handler for interrupt */
	while (1) /* Start of user input loop */
	{
		if (cond == -1)
		{
			status = params->status;
			_printf("Lydia&Alvin($) \n"); /* Prompt for user input */
			free_params(params); /* Deallocate parameter structure */
			return (status);
		}
		for (i = 0; i < BUFFER_SIZE; i++) /* Initialize input buffer */
			(params->buffer)[i] = 0;
		params->tokCount = 0;
		if (isatty(STDIN_FILENO)) /* Check if input is terminal */
			_printf("Lydia&Alvin($): ");
		cond = getline(&params->buffer, &size, stdin); /* Read user input */
		params->lineCount++; /* Increment line counter */
		if (cond == -1 && _strlen(params->buffer) == 0)
		{
			status = params->status;
			free_params(params);
			return (status);
		}
		state = NULL;
		params->nextCommand = _strtok(params->buffer, ";\n", &state);
		while (params->nextCommand)
		{
			params->tokCount = process_string(params); /* Parse command string */
			if (params->tokCount == 0)
				break;
			run_command(params); /* Execute command */
			for (i = 0; i < params->argsCap; i++)
			{
				free(params->args[i]); /* Clear argument list */
				params->args[i] = NULL;
			}
			params->tokCount = 0;
			free(params->nextCommand); /* Clear previous command */
			params->nextCommand = _strtok(params->buffer, ";\n", &state);		}
	}
}

/**
 * init_param - Creates and initializes shell parameter structure
 * @argv: command line arguments
 * @env: environment variables
 * Return: Initialized parameter structure
 */
param_t *init_param(char **argv, char **env)
{
	unsigned int i;
	char *eqs = NULL;
	param_t *params = malloc(sizeof(*params)); /* Allocate parameter structure */

	if (!params)
		return (NULL);
	params->argsCap = 10;
	params->lineCount = 0;
	params->tokCount = 0;
	params->status = 0;
	params->argv = argv;
	params->nextCommand = NULL;
	params->buffer = malloc(sizeof(char) * BUFFER_SIZE);
	if (!(params->buffer))
	{
		free(params);
		exit(-1);
	}
	for (i = 0; i < BUFFER_SIZE; i++) /* Initialize input buffer */
		params->buffer[i] = 0;
	params->args = malloc(sizeof(char *) * params->argsCap);
	if (!(params->args))
	{
		free(params->buffer);
		free(params);
		exit(-1);
	}
	for (i = 0; i < params->argsCap; i++) /* Initialize arguments list */
		params->args[i] = NULL;
	params->env_head = NULL;
	for (i = 0; env[i]; i++)
	{
		eqs = _strchr(env[i], '='); /* Split environment variable key-value pair */
		*eqs = '\0';
		params->env_head = add_node(&(params->env_head), env[i], eqs + 1);
		if (!(params->env_head))
		{
			free(params->buffer);
			free(params->args);
			free_list(params->env_head);
			free(params);
			exit(-1);
		}
	}
	params->alias_head = NULL;
	return (params);
}

