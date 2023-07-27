#include "shell.h"

/**
 * exitt - Exits the shell
 * @args: The command line arguments
 *
 * Return: 0 if successful, 1 otherwise
 */
int exitt(char **args)
{
	if (args[1] != NULL)
	{
		printf("hsh: exit: too many arguments\n");
		return (1);
	}
	return (0);
}

/**
 * env - Prints the current environment
 * @args: The command line arguments
 *
 * Return: 1 if successful, 0 otherwise
 */
int env(char **args __attribute__((unused)))
{
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return (1);
}

