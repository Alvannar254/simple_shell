#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "shell.h"
#include "lists.h"
#include "main.h"

/**
 * run_command - Executes commands from parameters
 * @params: Struct with parameters for command execution
 */
void run_command(param_t *params)
{
	/* Pointers to executable file and built-in function */
	char *exeFile = NULL;
	pid_t pid;
	void (*buildin)(param_t *);

	/* Get built-in function from the parameters */
	buildin = get_builtin(params);
	if (buildin) /* If built-in function exists, execute it */
	{
		buildin(params);
		return;
	}

	/* Search for executable file in the system path */
	exeFile = get_file(params);
	if (!exeFile) /* If no executable file is found, exit function */
	{
		return;
	}

	/* Create a child process */
	pid = fork();
	if (pid < 0) /* If fork fails, free parameters and exit with error code */
	{
		free_params(params);
		exit(98);
	}
	else if (pid == 0) /* In child process, execute the command */
	{
		execve(exeFile, params->args, NULL);
	}
	else /* In parent process, wait for child to finish and get its status */
	{
		wait(&params->status);
		params->status = WEXITSTATUS(params->status);
		free(exeFile);
	}
}

