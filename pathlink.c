#include "shell.h"


/**
 * getglobalenv - gets the value of the global variable
 * @name: name of the global variable
 *
 * Return: string of value
 */
char *getglobalenv(const char *name)
{
	int i, j;
	char *value;

	if (!name)
		return (NULL);
	for (i = 0; environ[i]; i++)
	{
		j = 0;
		if (name[j] == environ[i][j])
		{
			while (name[j])
			{
				if (name[j] != environ[i][j])
					break;

				j++;
			}
			if (name[j] == '\0')
			{
				value = (environ[i] + j + 1);
				return (value);
			}
		}
	}
	return (0);
}


/**
 * addnodeendstr - adds a new node at the end of a list_t list
 * @head: pointer to pointer to our linked list
 * @str: pointer to string in previous first node
 *
 * Return: address of the new element/node
 */

list_path *addnodeendstr(list_path **head, char *str)
{

	list_path *tmp;
	list_path *new;

	new = malloc(sizeof(list_path));

	if (!new || !str)
	{
		return (NULL);
	}

	new->dir = str;

	new->p = '\0';
	if (!*head)
	{
		*head = new;
	}
	else
	{
		tmp = *head;

		while (tmp->p)
		{

			tmp = tmp->p;
		}

		tmp->p = new;
	}

	return (*head);
}


/**
 * listpathdr - creates a linked list for path directories
 * @path: string of path value
 *
 * Return: pointer to the created linked list
 */
list_path *listpathdr(char *path)
{
	list_path *head = '\0';
	char *token;
	char *cpath = _strdup(path);

	token = strtok(cpath, ":");
	while (token)
	{
		head = addnodeendstr(&head, token);
		token = strtok(NULL, ":");
	}

	return (head);
}

/**
 * pathnamefile - finds the pathname of a filename
 * @filename: name of file or command
 * @head: head of linked list of path directories
 *
 * Return: pathname of filename or NULL if no match
 */
char *pathnamefile(char *filename, list_path *head)
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

/**
 * freelist_t - frees a list_t
 *@head: pointer to our linked list
 */
void freelist_t(list_path *head)
{
	list_path *storage;

	while (head)
	{
		storage = head->p;
		free(head->dir);
		free(head);
		head = storage;
	}

}

