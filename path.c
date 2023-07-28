#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "main.h"
#include "shell.h"
#include "lists.h"

/**
 * check_direct_access - Checks if the command can be accessed directly
 * @params: Reference parameters
 *
 * Return: Duplicated string of the command if it can be accessed, NULL
 */
char *check_direct_access(param_t *params)
{
	char *directAccess = NULL;

	if (access(params->args[0], F_OK | X_OK) == 0)
	{
		directAccess = _strdup(params->args[0]);
		return (directAccess);
	}
	if (errno == EACCES)
	{
		params->status = 126;
		write_error(params, "Permission denied\n");
	}
	return (NULL);
}

/**
 * check_path_access - Checks if the command can be accessed from PATH
 * @params: Reference parameters
 * @path: PATH environment variable
 *
 * Return: Full path to the command if it can be accessed, NULL otherwise
 */
char *check_path_access(param_t *params, char *path)
{
	char *exePath = NULL, *exeArg = NULL, *tmp = NULL;
	char *state = NULL;

	exePath = _strtok(path, ":", &state);
	while (exePath)
	{
		tmp = exeArg;
		exeArg = str_concat(exePath, "/");
		free(tmp);
		tmp = exeArg;
		exeArg = str_concat(exeArg, params->args[0]);
		free(tmp);
		if (access(exeArg, F_OK) == 0)
		{
			free(exePath);
			return (exeArg);
		}
		free(exePath);
		exePath = _strtok(path, ":", &state);
	}
	params->status = 127;
	write_error(params, "not found\n");
	free(exePath);
	free(exeArg);
	return (NULL);
}

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
	char *directAccess = check_direct_access(params);

	if (directAccess != NULL)
	{
		return (directAccess);
	}
	path = _getenv("PATH", params);
	if (!path)
	{
		write_error(params, "not found\n");
		return (NULL);
	}
	return (check_path_access(params, path));
}

