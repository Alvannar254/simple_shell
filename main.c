#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

/* Function prototypes */
int execute_command(char *command);
char *locate_command(char *command);
void print_environment(void);

/* Function descriptions */

/**
 * main - Entry point of the shell program
 *
 * Return: Always 0
 */
int main(void)
{
	char *command;
	size_t bufsize = 1024;
	ssize_t characters;

	while (1)
	{
		/* Display the prompt */
		printf("($) ");

		/* Read the user input */
		command = (char *)malloc(bufsize * sizeof(char));
		if (command == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		characters = getline(&command, &bufsize, stdin);
		if (characters == -1)
		{
			/* Handle end of file (Ctrl+D) */
			free(command);
			putchar('\n');
			break;
		}

		/* Remove the newline character at the end of the command */
		if (characters > 0 && command[characters - 1] == '\n')
			command[characters - 1] = '\0';

		/* Check if the command is "exit" */
		if (strcmp(command, "exit") == 0)
		{
			free(command);
			putchar('\n');
			break;
		}
		/* Check if the command is "env" */
		else if (strcmp(command, "env") == 0)
		{
			/* Print the current environment variables */
			print_environment();
		}
		else
		{
			/* Execute the command */
			execute_command(command);
		}

		free(command);
	}

	return (0);
}

