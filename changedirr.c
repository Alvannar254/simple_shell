#include <unistd.h>
#include <stdlib.h>
#include "shell.h"
#include "main.h"

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
	char *target = NULL, cwd[1024];
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
		if (!_strcmp(params->args[1], "-"))
		{
			target = _getenv("OLDPWD", params);
			if (!target)
			{
				params->status = 0;
				target = _getenv("PWD", params);
				_printf("%s\n", target);
				free(target);
				return;
			}
			_printf("%s\n", target);
		}
		else
		{
			params->status = 2;
			_printf("%s: %d: cd: Illegal option %c%c\n",
					params->argv[0], params->lineCount,
					'-', params->args[1][1]);
			return;
		}
	}
	/* If directory argument is provided, set it as the target */
	else
	{
		target = _strdup(params->args[1]);
		if (!target)
		{
			write(STDERR_FILENO, "cd target malloc error\n", 18);
			exit(-1);
		}
	}
	/* Attempt to change to the target directory */
	i = chdir(target);
	if (i)
	{
		write_error(params, "can't cd to ");
		write(STDERR_FILENO, target, _strlen(target));
		write(STDERR_FILENO, "\n", 1);
		params->status = 0;
		free(target);
		return;
	}
	free(target);
	tmpArgs = malloc(sizeof(char *) * 3);
	if (!tmpArgs)
		exit(-1);
	originArgs = params->args;
	params->args = tmpArgs;
	params->tokCount = 3;

	/* Replace OLDPWD environment variable with the current PWD */
	tmpArgs[0] = _strdup("setenv");
	tmpArgs[1] = _strdup("OLDPWD");
	if (!tmpArgs[0] || !tmpArgs[1])
	{
		write(STDERR_FILENO, "cd old PWD malloc error\n", 18);
		free_params(params);
		exit(-1);
	}
	tmpArgs[2] = _getenv("PWD", params);
	_setenv(params);
	for (i = 0; i < 3; i++)
		free(tmpArgs[i]);

	/* Set PWD environment variable to the new working directory */
	tmpArgs[0] = _strdup("setenv");
	tmpArgs[1] = _strdup("PWD");
	tmpArgs[2] = _strdup(getcwd(cwd, 1024));
	if (!tmpArgs[0] || !tmpArgs[1] || !tmpArgs[2])
	{
		write(STDERR_FILENO, "cd new PWD malloc error\n", 18);
		free_params(params);
		exit(-1);
	}
	_setenv(params);
	for (i = 0; i < 3; i++)
		free(tmpArgs[i]);
	free(tmpArgs);

	/* Return to the original command-line arguments */
	params->args = originArgs;
}

