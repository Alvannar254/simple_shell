#include <stdlib.h>
#include <string.h>

/**
 * find_path - searches the PATH for a command
 * @cmd: the command to find
 * Return: the full path to the command, or NULL if not found
 */
char *find_path(char *cmd)
{
	char *PATH = getenv("PATH");
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

