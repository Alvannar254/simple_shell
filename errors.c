#include <unistd.h>
#include "shell.h"
#include "main.h"

/**
 * write_error - Prints a custom error message to stderr
 * @params: A struct containing command and program info
 * @msg: The error message to be printed
 *
 * Construct an error message from the provided parameters and
 * write the finalized message to stderr using system call.
 */
void write_error(param_t *params, char *msg)
{
	char errBuffer[1024] = {0};  /* buffer to store error message */
	char *writeHead = errBuffer, *bufPtr = errBuffer; /* buffer pointers */

	/* add the program name to the error message */
	_strcpy(writeHead, params->argv[0]);
	writeHead = bufPtr + _strlen(bufPtr);

	/* add a separator */
	_strcpy(writeHead, ": ");
	writeHead = bufPtr + _strlen(bufPtr);

	/* add the line count to the error message */
	_strcpy(writeHead, get_number(params->lineCount));
	writeHead = bufPtr + _strlen(bufPtr);

	/* add another separator */
	_strcpy(writeHead, ": ");
	writeHead = bufPtr + _strlen(bufPtr);

	/* add the command name to the error message */
	_strcpy(writeHead, params->args[0]);
	writeHead = bufPtr + _strlen(bufPtr);

	/* add another separator */
	_strcpy(writeHead, ": ");
	writeHead = bufPtr + _strlen(bufPtr);

	/* add the error message to the error message */
	_strcpy(writeHead, msg);
	writeHead = bufPtr + _strlen(bufPtr);

	/* write the error message to stderr */
	write(STDERR_FILENO, errBuffer, _strlen(bufPtr));
}

