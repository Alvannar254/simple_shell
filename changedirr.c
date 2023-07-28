#include <unistd.h>
#include <stdlib.h>
#include "shell.h"
#include "main.h"

/**
 * handle_cd_error - Handles errors for the _cd function
 * @params: Parameters of the shell
 * @target: The target directory
 */
void handle_cd_error(param_t *params, char *target)
{
	write_error(params, "can't cd to ");
	write(STDERR_FILENO, target, _strlen(target));
	write(STDERR_FILENO, "\n", 1);
	params->status = 0;
	free(target);
}

/**
 * handle_cd_dash - Handles '-' argument for the _cd function
 * @params: Parameters of the shell
 *
 * Return: The target directory
 */
char *handle_cd_dash(param_t *params)
{
	char *target;

	target = _getenv("OLDPWD", params);
	if (!target)
	{
		params->status = 0;
		target = _getenv("PWD", params);
		_printf("%s\n", target);
		free(target);
	}
	else
	{
		_printf("%s\n", target);
	}

	return (target);
}

/**
 * handle_cd_arg - Handles directory argument for the _cd function
 * @params: Parameters of the shell
 *
 * Return: The target directory
 */
char *handle_cd_arg(param_t *params)
{
	char *target;

	target = _strdup(params->args[1]);
	if (!target)
	{
		write(STDERR_FILENO, "cd target malloc error\n", 18);
		exit(-1);
	}

	return (target);
}

/**
 * update_pwd - Updates the PWD and OLDPWD environment variables
 * @params: Parameters of the shell
 * @tmpArgs: Temporary arguments
 * @originArgs: Original arguments
 */
void update_pwd(param_t *params, char **tmpArgs, char **originArgs)
{
	char cwd[1024];
	int i;

	/* Replace OLDPWD environment variable with the current PWD */
	tmpArgs[0] = _strdup("setenv");
	tmpArgs[1] = _strdup("OLDPWD");
	tmpArgs[2] = _getenv("PWD", params);
	_setenv(params);
	for (i = 0; i < 3; i++)
		free(tmpArgs[i]);

	/* Set PWD environment variable to the new working directory */
	tmpArgs[0] = _strdup("setenv");
	tmpArgs[1] = _strdup("PWD");
	tmpArgs[2] = _strdup(getcwd(cwd, 1024));
	_setenv(params);
	for (i = 0; i < 3; i++)
		free(tmpArgs[i]);
	free(tmpArgs);

	/* Return to the original command-line arguments */
	params->args = originArgs;
}

/**
 * _cd - Alters the present working directory.
 *
 * @params: Parameters of the shell.
 *
 * Switches the current directory based on input parameters.
 * If no argument is given, it changes to the HOME directory.
 * If '-' is provided, it changes to the previous directory.
 * Otherwise, it changes to the directory provided in the argument.
 * The function also updates the OLDPWD and PWD environment variables.
 */
void _cd(param_t *params)
{
	char *target = NULL;
	char **tmpArgs = NULL, **originArgs = NULL;
	int i;

	/* If no directory specified, switch to user's home directory */
	if (params->tokCount == 1)
	{
		target = _getenv("HOME", params);
		if (!target)
		{
			params->status = 0;
			return;
		}
	}
	/* When '-' is used as argument, revert to the last directory */
	else if (params->args[1][0] == '-')
	{
		target = handle_cd_dash(params);
	}
	/* If directory argument is provided, set it as the target */
	else
	{
		target = handle_cd_arg(params);
	}

	i = chdir(target);
	if (i)
	{
		handle_cd_error(params, target);
		return;
	}
	free(target);
	tmpArgs = malloc(sizeof(char *) * 3);
	if (!tmpArgs)
		exit(-1);
	originArgs = params->args;
	params->args = tmpArgs;
	params->tokCount = 3;

	update_pwd(params, tmpArgs, originArgs);
}

