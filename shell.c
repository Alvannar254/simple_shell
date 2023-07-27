#include "shell.h"

/**
 * main - Entry point of the shell
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	int status = 1;

	while (status)
	{
		printf("#cisfun$ ");
		getline(&line, &len, stdin);
		status = execute_command(line);
	}
	free(line);
	return (0);
}

