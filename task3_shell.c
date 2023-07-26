#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* Function prototypes */
int execute_command(char *command);
char *locate_command(char *command);

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

		/* Execute the command */
		if (execute_command(command) == -1)
			printf("%s: command not found\n", command);

		free(command);
	}

	return (0);
}

/**
 * execute_command - Execute the given command
 * @command: The command to be executed
 *
 * Return: 0 on success, -1 on failure
 */
int execute_command(char *command)
{
	char *args[64]; /* Array to store command and arguments */
	pid_t pid;      /* Declaration moved to the beginning of the function */
	char *full_path_command;

	/* Tokenize the command and arguments */
	char *token;
	int arg_count = 0;

	token = strtok(command, " ");
	while (token != NULL)
	{
		args[arg_count] = token;
		arg_count++;
		token = strtok(NULL, " ");
	}

	if (arg_count == 0)
		return (0); /* No command found */

	args[arg_count] = NULL; /* NULL-terminate the args array */

	full_path_command = locate_command(args[0]);
	if (!full_path_command)
		return (-1); /* Command not found */

	/* Fork a child process to execute the command */
	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return (0);
	}
	else if (pid == 0)
	{
		/* Child process */
		if (execve(full_path_command, args, NULL) == -1)
		{
			perror("execve");
			free(full_path_command);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		wait(NULL); /* Wait for the child process to complete */
	}

	free(full_path_command);
	return (1);
}

/**
 * locate_command - Locate a command in the directories specified by the PATH
 * @command: The command to be located
 *
 * Return: The full path to the command, or NULL if the command cannot be found
 */
char *locate_command(char *command)
{
	struct stat st;
	char *PATH = getenv("PATH");
	char *dir = strtok(PATH, ":");
	char *full_path_command = malloc(256); /* Calculate size needed */

	while (dir)
	{
		sprintf(full_path_command, "%s/%s", dir, command);

		if (stat(full_path_command, &st) == 0)
			return (full_path_command);

		dir = strtok(NULL, ":");
	}

	free(full_path_command);
	return (NULL);
}

