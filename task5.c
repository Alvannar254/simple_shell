#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "main.h"

#define MAXARGS 128

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

/**
 * execute_command - forks a child process to execute a command
 * @line: the command to execute
 * Return: the exit status of the command
 */
int execute_command(char *line)
{
	char *argv[MAXARGS];
	int i = 0;
	pid_t child_pid;
	int status;
	char *path;

	argv[i] = strtok(line, " ");
	while (argv[i] != NULL)
	{
		i++;
		argv[i] = strtok(NULL, " ");
	}

	/* Check if the command is "exit" */
	if (strcmp(argv[0], "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}

	/* Check if the command is "env" */
	if (strcmp(argv[0], "env") == 0)
	{
		for (i = 0; environ[i] != NULL; i++)
		{
			printf("%s\n", environ[i]);
		}
		return (0);
	}

	if (strchr(argv[0], '/') != NULL) /* If the command includes a path */
	{
		path = strdup(argv[0]); /* Duplicate the command */
	}
	else
	{
		path = find_path(argv[0]);
	}

	if (path == NULL || access(path, X_OK) != 0)
	{
		fprintf(stderr, "%s: command not found\n", argv[0]);
		free(path);
		return (1);
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		free(path);
		return (1);
	}
	if (child_pid == 0)
	{
		if (execve(path, argv, environ) == -1)
		{
			perror("./hsh");
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
	}
	free(path);
	return (0);
}

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

