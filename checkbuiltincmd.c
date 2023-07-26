#include "shell.h"

/**
* chbuildin - checks if the command is a buildin
* @wordarr: array of arguments
*
* Return: pointer to function that takes wordarr and returns void
*/

void(*chbuildin(char **wordarr))(char **wordarr)
{
	int i, j;
	mbuild T[] = {
		{"exit", exitt},
		{"env", env},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{NULL, NULL}
	};

	for (i = 0; T[i].name; i++)
	{
		j = 0;
		if (T[i].name[j] == wordarr[0][j])
		{
			for (j = 0; wordarr[0][j]; j++)
			{
				if (T[i].name[j] != wordarr[0][j])
					break;
			}
			if (!wordarr[0][j])
				return (T[i].func);
		}
	}
	return (0);

