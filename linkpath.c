#include "main.h"
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

#define MAXARGS 128

/**
 * _getenv - gets the value of the global variable
 * @name: name of the global variable
 * Return: string of value
 */
char *_getenv(const char *name)
{
	int i, j;
	char *value;

	if (!name)
		return (NULL);
	for (i = 0; environ[i]; i++)
	{
		j = 0;
		if (name[j] == environ[i][j])
		{
			while (name[j])
			{
				if (name[j] != environ[i][j])
					break;

				j++;
			}
			if (name[j] == '\0')
			{
				value = (environ[i] + j + 1);
				return (value);
			}
		}
	}
	return (NULL);
}

/**
 * find_path - searches the PATH for a command
 * @cmd: the command to find
 * Return: the full path to the command, or NULL if not found
 */
char *find_path(char *cmd)
{
	char *PATH = _getenv("PATH");
	char *PATH_copy = strdup(PATH); /* Make a copy of PATH */
	char *p = strtok(PATH_copy, ":");
	char *filepath = malloc(256);

	while (p != NULL)
	{
		sprintf(filepath, "%s/%s", p, cmd);
		if (access(filepath, X_OK) == 0)
		{
			free(PATH_copy);
			return (filepath);
		}
		p = strtok(NULL, ":");
	}
	free(PATH_copy);
	free(filepath);
	return (NULL);
}

