#include <unistd.h>
#include <stdlib.h>
#include "shell.h"
#include "main.h"
#define BUFFER_SIZE 4096
#define READ_SIZE 1024

/**
 * rlLine - Reallocate line buffer memory
 * @line: Pointer to the buffer
 * @oldSize: Current buffer size
 * @newSize: Target buffer size
 *
 * Return: Pointer to the newly allocated buffer
 */
char *rlLine(char **line, unsigned int oldSize, unsigned int newSize)
{
	char *newLine = NULL;
	unsigned int i;

	newLine = malloc(newSize); /* Allocate new memory */
	if (newLine)
	{
		for (i = 0; i < oldSize; i++)
			newLine[i] = (*line)[i]; /* Copy old buffer content */
		free(*line); /* Free old buffer */
		*line = newLine; /* Update pointer */
	}
	return (newLine);
}

/**
 * _getline - Read a line from standard input
 * @params: Parameters for getline function
 *
 * Return: Length of the line read
 */
int _getline(param_t *params)
{
	char *line = NULL;
	static unsigned int bufSize = BUFFER_SIZE; /* Starting buffer size */
	char *writeHead = line; /* Points to writing position */
	unsigned int len;

	line = malloc(BUFFER_SIZE); /* Allocate initial memory */
	do {
		len = read(0, writeHead, BUFFER_SIZE); /* Read input */
		if (len == 0)
			break;
		writeHead += len; /* Move writing position */
		if (writeHead >= (line + BUFFER_SIZE - 1 - READ_SIZE))
		{
			line = rlLine(&line, bufSize, bufSize * 2); /* Reallocate memory */
			bufSize *= 2; /* Update buffer size */
		}
	} while (*(writeHead - 1) != '\n'); /* Continue if last char is not newline */

	free(params->buffer); /* Free old buffer */
	params->buffer = line; /* Update buffer pointer */
	if (len == 0)
		return (-1); /* If read() reads 0 chars, return -1 */
	return (_strlen(params->buffer)); /* Return length of the read line */
}

