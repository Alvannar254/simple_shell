#include "main.h"

/**
 * shellexit - exits the shell with or without a return of status n
 * @wordar: array of words of the entered line
 *
 *exit(0)
 */

void shellexit(char **wordar)
{
	int i, n;

	if (wordar[1])
	{
		n = strtoint(wordar[1]);
		if (n <= -1)
			n = 2;
		freewordar(wordar);
		exit(n);
	}
	for (i = 0; wordar[i]; i++)
		free(wordar[i]);
	free(wordar);
	exit(0);
}



/**
 * strtoint - converts a string into an integer
 *@stp: pointer to a string
 *
 *Return: the integer
 */


int strtoint(char *stp)
{
	int i, integer, sign = 1;

	i = 0;
	integer = 0;
	while (!((stp[i] >= '0') && (stp[i] <= '9')) && (stp[i] != '\0'))
	{
		if (stp[i] == '-')
		{
			sign = sign * (-1);
		}
		i++;
	}
	while ((stp[i] >= '0') && (stp[i] <= '9'))
	{
		integer = (integer * 10) + (sign * (stp[i] - '0'));
		i++;
	}
	return (integer);
}

/**
 * currenv - prints the current environment
 * @wordar: array of arguments
 *
 *exit(0)
 */
 
void currenv(char **wordar __attribute__ ((unused)))
{

	int i;

	for (i = 0; environ[i]; i++)
	{
		_puts(environ[i]);
		_puts("\n");
	}

}


/**
 * newenv - Initialize a new environment variable, or modify an existing one
 * @wordar: array of entered words
 *
 *return
 */
 
void newenv(char **wordar)
{
	int i, j, k;

	if (!wordar[1] || !wordar[2])
	{
		perror(_getenv("_"));
		return;
	}

	for (i = 0; environ[i]; i++)
	{
		j = 0;
		if (wordar[1][j] == environ[i][j])
		{
			while (wordar[1][j])
			{
				if (wordar[1][j] != environ[i][j])
					break;

				j++;
			}
			if (wordar[1][j] == '\0')
			{
				k = 0;
				while (wordar[2][k])
				{
					environ[i][j + 1 + k] = wordar[2][k];
					k++;
				}
				environ[i][j + 1 + k] = '\0';
				return;
			}
		}
	}
	if (!environ[i])
	{

		environ[i] = concat_all(wordar[1], "=", wordar[2]);
		environ[i + 1] = '\0';

	}
}


/**
 * rmenv - Remove an environment variable
 * @wordar: array of entered words
 *
 *return
 */

void rmenv(char **wordar)
{
	int i, j;

	if (!wordar[1])
	{
		perror(_getenv("_"));
		return;
	}
	for (i = 0; environ[i]; i++)
	{
		j = 0;
		if (wordar[1][j] == environ[i][j])
		{
			while (wordar[1][j])
			{
				if (wordar[1][j] != environ[i][j])
					break;

				j++;
			}
			if (wordar[1][j] == '\0')
			{
				free(environ[i]);
				environ[i] = environ[i + 1];
				while (environ[i])
				{
					environ[i] = environ[i + 1];
					i++;
				}
				return;
			}
		}
	}
}

