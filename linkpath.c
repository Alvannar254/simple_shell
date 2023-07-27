#include "shell.h"

/**
 * _getenv - gets the value of the global variable
 * @name: name of the global variable
 * Return: string of value
 */
char *_getenv(const char *name)
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
 * add_node_end - adds a new node at the end of a list_t list
 * @head: pointer to pointer to our linked list
 * @str: pointer to string in previous first node
 * Return: address of the new element/node
 */
list_t *add_node_end(list_t **head, char *str)
{
	list_t *tmp;
	list_t *new;

	new = malloc(sizeof(list_t));

	if (!new || !str)
	{
		return (NULL);
	}

	new->str = str;
	new->next = NULL;
	if (!*head)
	{
		*head = new;
	}
	else
	{
		tmp = *head;

		while (tmp->next)
		{
			tmp = tmp->next;
		}

		tmp->next = new;
	}

	return (*head);
}

/**
 * linkpath - creates a linked list for path directories
 * Return: pointer to the created linked list
 */
list_t *linkpath(void)
{
	char *path = _getenv("PATH");
	char *token;
	char *cpath = strdup(path);
	list_t *head = NULL;

	token = strtok(cpath, ":");
	while (token)
	{
		head = add_node_end(&head, token);
		token = strtok(NULL, ":");
	}

	return (head);
}

/**
 * concat_all - Concatenates three strings
 * @str1: The first string
 * @str2: The second string
 * @str3: The third string
 *
 * Return: Pointer to the concatenated string
 */
char *concat_all(char *str1, char *str2, char *str3)
{
	char *new_str;
	int len1, len2, len3;

	len1 = strlen(str1);
	len2 = strlen(str2);
	len3 = strlen(str3);

	new_str = malloc((len1 + len2 + len3 + 1) * sizeof(char));
	if (!new_str)
	{
		perror("Error: ");
		return (NULL);
	}

	strcpy(new_str, str1);
	strcat(new_str, str2);
	strcat(new_str, str3);

	return (new_str);
}

/**
 * _which - finds the pathname of a filename
 * @filename: name of file or command
 * @head: head of linked list of path directories
 * Return: pathname of filename or NULL if no match
 */
char *_which(char *filename, list_t *head)
{
	struct stat st;
	char *string;

	list_t *tmp = head;

	while (tmp)
	{
		string = concat_all(tmp->str, "/", filename);
		if (stat(string, &st) == 0)
		{
			return (string);
		}
		free(string);
		tmp = tmp->next;
	}

	return (NULL);
}

