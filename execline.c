#include "shell.h"


/**
 * spltstr - splits a string and makes it an array of pointers to words
 * @str: the string to be split
 * @delimit: the delimititer
 *
 * Return: array of pointers to words
 */

char **spltstr(char *str, const char *delimit)
{
	int i, xy;
	char **array;
	char *token;
	char *copy;

	copy = malloc(_strlen(str) + 1);
	if (copy == NULL)
	{
		perror(_getenv("_"));
		return (NULL);
	}
	i = 0;
	while (str[i])
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';

	token = strtok(copy, delimit);
	array = malloc((sizeof(char *) * 2));
	array[0] = _strdup(token);

	i = 1;
	xy = 3;
	while (token)
	{
		token = strtok(NULL, delimit);
		array = relmem(array, (sizeof(char *) * (xy - 1)), (sizeof(char *) * xy));
		array[i] = _strdup(token);
		i++;
		xy++;
	}
	free(copy);
	return (array);
}

/**
 * commexec - executes a command
 * @argarr: array of arguments
 *
 *exit
 */

void commexec(char **argarr)
{

	int f, status;

	if (!argarr || !argarr[0])
		return;
	f = fork();
	if (f == -1)
	{
		perror(_getenv("_"));
	}
	if (f == 0)
	{
		execve(argarr[0], argarr, environ);
			perror(argarr[0]);
		exit(EXIT_FAILURE);
	}
	wait(&status);
}

/**
 * relmem - Reallocates memory block
 * @prevptr: previous pointer
 * @oldptrsize: old size of previous pointer
 * @newptrsize: new size for our pointer
 *
 * Return: New resized Pointer
 */

void *relmem(void *prevptr, unsigned int oldptrsize, unsigned int newptrsize)
{
	char *new;
	char *old;

	unsigned int i;

	if (prevptr == NULL)
		return (malloc(newptrsize));

	if (newptrsize == oldptrsize)
		return (prevptr);

	if (newptrsize == 0 && prevptr != NULL)
	{
		free(prevptr);
		return (NULL);
	}

	new = malloc(newptrsize);
	old = prevptr;
	if (new == NULL)
		return (NULL);

	if (newptrsize > oldptrsize)
	{
		for (i = 0; i < oldptrsize; i++)
			new[i] = old[i];
		free(prevptr);
		for (i = oldptrsize; i < newptrsize; i++)
			new[i] = '\0';
	}
	if (newptrsize < oldptrsize)
	{
		for (i = 0; i < newptrsize; i++)
			new[i] = old[i];
		free(prevptr);
	}
	return (new);
}

/**
 * freewordarr - frees the array of pointers wordarr
 *@wordarr: array of pointers
 *
 *exit.
 */

void freewordarr(char **wordarr)
{
	int i;

	for (i = 0; wordarr[i]; i++)
		free(wordarr[i]);
	free(wordarr);
}

