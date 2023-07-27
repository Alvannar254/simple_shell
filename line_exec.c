#include "shell.h"

/**
 * execute_command - Executes a command
 * @line: The command to execute
 *
 * Return: Always 0 (Success)
 */
int execute_command(char *line)
{
	char **args;
	pid_t pid;
	int status;

	args = splitstring(line);
	if (args == NULL)
	{
		return (1);
	}

	if (strcmp(args[0], "exit") == 0)
	{
		return (exitt(args));
	}
	else if (strcmp(args[0], "env") == 0)
	{
		return (env(args));
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			perror("Error");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("Error");
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	free(args);
	return (1);
}

