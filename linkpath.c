#include "shell.h"

/**
 * linkpath - Creates a linked list of PATH directories
 *
 * Return: A linked list of PATH directories
 */
list_t *linkpath(void)
{
	char *path = _getenv("PATH");
	char *dir = strtok(path, ":");
	list_t *head = NULL;

	while (dir != NULL)
	{
		add_node_end(&head, dir);
		dir = strtok(NULL, ":");
	}

	return (head);
}

/**
 * _which - Finds the full path of a command
 * @cmd: The command to find
 * @head: The linked list of PATH directories
 *
 * Return: The full path of the command, or NULL if the command is not found
 */
char *_which(char *cmd, list_t *head)
{
	char *path;
	struct stat st;

	while (head != NULL)
	{
		path = concat_all(head->str, "/", cmd);
		if (stat(path, &st) == 0)
		{
			return (path);
		}
		free(path);
		head = head->next;
	}

	return (NULL);
}

