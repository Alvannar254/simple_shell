#include "shell.h"




/**
 * linkpath - creates a linked list for path directories
 * @path: string of path value
 * Return: pointer to the created linked list
 */
list_path *linkpath(char *path)
{
	list_path *head = '\0';
	char *token;
	char *cpath = _strdup(path);

	token = strtok(cpath, ":");
	while (token)
	{
		head = add_node_end(&head, token);
		token = strtok(NULL, ":");
	}

	return (head);
}
