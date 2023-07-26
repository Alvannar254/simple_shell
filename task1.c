#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * execute_command - forks a child process to execute a command
 * @line: the command to execute
 * Return: the exit status of the command
 */
int execute_command(char *line)
{
	char *argv[2];
	int status;
	pid_t child_pid;

	argv[0] = line;
	argv[1] = NULL;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return (1);
	}
	if (child_pid == 0)
	{
		if (execve(line, argv, NULL) == -1)
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

