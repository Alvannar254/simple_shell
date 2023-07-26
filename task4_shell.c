#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/* Function prototypes */
int execute_command(char *command);

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

		/* Execute the command */
		execute_command(command);

		free(command);
	}

	return (0);
}

/**
 * execute_command - Execute the given command
 * @command: The command to be executed
 *
 * Return: 1 on success, 0 on failure
 */
int execute_command(char *command)
{
	pid_t pid;
	char *path = "/bin/";
	char *full_command = (char *)malloc(strlen(path) + strlen(command) + 1);

	if (full_command == NULL)
	{
		perror("malloc");
		return (0);
	}

	/* Combine the path and command to form the full command path */
	strcpy(full_command, path);
	strcat(full_command, command);

	/* Fork to create a child process */
	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		free(full_command);
		return (0);
	}
	else if (pid == 0)
	{
		/* Child process */
		char *args[2];

		args[0] = full_command;

		args[1] = NULL;

		if (execve(args[0], args, NULL) == -1)
		{
			perror("execve"); /* Execve returns only on error */
			free(full_command);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		wait(NULL); /* Wait for the child process to complete */
	}

	free(full_command);
	return (1);
}

