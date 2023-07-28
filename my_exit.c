#include <stdlib.h>
#include <limits.h>
#include "shell.h"
#include "main.h"

/**
 * validNum - Validates if input string is a number
 * @s: Input string to validate
 *
 * Return: 0 if not a number, 1 if a number
 */
int validNum(char *s)
{
	while (*s) /* Loop through each character in the string */
	{
		if (*s > '9' || *s < '0') /* If char is not in range of '0' - '9' */
			return (0); /* Return false (0) - not a valid number */
		s++; /* Move to next char */
	}
	return (1); /* If no false returned in loop, return true (1) */
}

/**
 * _myExit - Built-in function for shell exit
 * @params: Parameters from the shell
 */
void _myExit(param_t *params)
{
	int status = 0; /* Declare and initialize status variable */

	if (!params->args[1]) /* If no exit status argument is passed */
	{
		status = params->status; /* Set current status */
		free_params(params); /* Free allocated memory */
		exit(status); /* Exit with the status */
	}
	if (validNum(params->args[1])) /* If passed argument is a valid number */
	{
		status = _atoi((params->args)[1]); /* Convert string to int */
		if (status == -1) /* If _atoi returns -1, invalid number */
		{
			write_error(params, "Illegal number: "); /* Write error message */
			write(STDERR_FILENO, params->args[1], _strlen(params->args[1]));
			write(STDERR_FILENO, "\n", 1); /* Write a newline character */
			params->status = 2; /* Set status to 2 */
			return; /* Return to caller */
		}
		free_params(params); /* Free allocated memory */
		exit(status); /* Exit with the status */
	}
	else /* If not a valid number */
	{
		params->status = 2; /* Set status to 2 */
		write_error(params, "Illegal number: "); /* Write error message */
		write(STDERR_FILENO, params->args[1], _strlen(params->args[1]));
		write(STDERR_FILENO, "\n", 1); /* Write a newline character */
	}
}

