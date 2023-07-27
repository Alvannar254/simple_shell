#include "shell.h"



/**
 * add_node_end - adds a new node at the end of a list_t list
 * @head: pointer to pointer to our linked list
 * @str: pointer to string in previous first node
 * Return: address of the new element/node
 */

list_path *add_node_end(list_path **head, char *str)
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
