#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "main.h"
#include "shell.h"
#include "lists.h"

/**
 * get_file - Acquires the right command file path
 * @params: Reference parameters
 *
 * Return: Path to command file or NULL if not available
 * Note: Returned string must be freed
 */
char *get_file(param_t *params)
{
	char *path = NULL;
	char *exePath = NULL, *exeArg = NULL, *tmp = NULL;
	char *state = NULL;

	if (access(params->args[0], F_OK | X_OK) == 0)
	{
		free(path);

		return (_strdup(params->args[0]));
	}
	if (errno == EACCES)
	{
		params->status = 126;

		write_error(params, "Permission denied\n");
		return (NULL);
	}
	path = _getenv("PATH", params);
	if (!path)
	{
		write_error(params, "not found\n");
		return (NULL);
	}

	exePath = _strtok(path, ":", &state);
	/* Traverses through all paths */
	while (exePath)
	{
		tmp = exeArg;

		exeArg = str_concat(exePath, "/");
		free(tmp);
		tmp = exeArg;
		/* Concatenates the command to the path */
		exeArg = str_concat(exeArg, params->args[0]);
		free(tmp);
		/* Checks for the file in the path */
		if (access(exeArg, F_OK) == 0)
		{
			free(path);
			free(exePath);
			/* Returns the executable path */
			return (exeArg);
		}
		free(exePath);
		exePath = _strtok(path, ":", &state);
	}
	params->status = 127;
	write_error(params, "not found\n");
	free(path);
	free(exePath);
	free(exeArg);
	return (NULL);
}

