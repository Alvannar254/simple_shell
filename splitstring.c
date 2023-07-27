#include "shell.h"

/**
 * splitstring - Splits a string into words
 * @line: The string to split
 *
 * Return: An array of words
 */
char **splitstring(char *line)
{
	int bufsize = 64, position = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token;

	if (!tokens)
	{
		fprintf(stderr, "hsh: allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\r\n\a");
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if (!tokens)
			{
				fprintf(stderr, "hsh: allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, " \t\r\n\a");
	}
	tokens[position] = NULL;
	return tokens;
}

