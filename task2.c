#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAXARGS 128

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

	argv[i] = strtok(line, " ");
	while (argv[i] != NULL)
	{
		i++;
		argv[i] = strtok(NULL, " ");
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return (1);
	}
	if (child_pid == 0)
	{
		if (execve(argv[0], argv, NULL) == -1)
		{
			perror("./shell");
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
	}
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

