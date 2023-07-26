#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

/**
 * main - entry point for the simple shell program
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		printf("#cisfun$ ");
		read = getline(&line, &len, stdin);
		if (read == -1) /* End of file (Ctrl+D) */
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		line[read - 1] = '\0'; /* Remove newline character */
		execute_command(line);
	}
	free(line);
	return (EXIT_SUCCESS);
}

