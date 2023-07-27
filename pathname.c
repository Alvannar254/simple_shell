#include "shell.h"



/**
 * _which - finds the pathname of a filename
 * @filename: name of file or command
 * @head: head of linked list of path directories
 * Return: pathname of filename or NULL if no match
 */
char *_which(char *filename, list_path *head)
{
	struct stat st;
	char *string;

	list_path *tmp = head;

	while (tmp)
	{

		string = concat_all(tmp->dir, "/", filename);
		if (stat(string, &st) == 0)
		{
			return (string);
		}
		free(string);
		tmp = tmp->p;
	}

	return (NULL);
}
