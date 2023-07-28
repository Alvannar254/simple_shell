#include <stdio.h>
#include <stdlib.h>
#include "lists.h"
#include "shell.h"
#include "main.h"

/**
 * list_len - Computes the number of elements in a linked list_t list.
 * @h: Pointer to the start of the list
 *
 * Return: The length of the list
 */
size_t list_len(list_t *h)
{
	size_t i;

	for (i = 0; h != 0; i++)
		h = h->next;
	return (i);
}

/**
 * print_list - Prints all the elements of a list_t list.
 * @h: Pointer to the start of the list
 *
 * Return: The length of the list
 */
size_t print_list(list_t *h)
{
	int count;

	for (count = 0; h != 0; count++)
	{
		if (h->str == NULL)
			break;
		_printf("%s\n", h->str);
		h = h->next;
	}
	return (count);
}

/**
 * add_node - Adds a new node at the beginning of a list_t list.
 * @head: Pointer to the start of the list
 * @str: Key to be added in the new node
 * @val: Value to be added in the new node
 *
 * Return: Pointer to the new head
 */
list_t *add_node(list_t **head, char *str, char *val)
{
	list_t *new;

	new = malloc(sizeof(list_t));
	if (new == NULL)
		return (NULL);
	new->str = _strdup(str);
	new->len = _strlen(new->str);
	new->val = _strdup(val);
	new->valLen = _strlen(val);
	new->next = *head;
	*head = new;

	return (new);
}

/**
 * get_node - Searches for a node in the linked list.
 * @head: Pointer to the start of the list
 * @str: Key to search for
 *
 * Return: Pointer to the desired node, NULL if not found
 */
list_t *get_node(list_t *head, char *str)
{
	list_t *h;

	if (!head)
		return (NULL);
	h = head;
	while (h)
	{
		if (!_strcmp(h->str, str))
			break;
		h = h->next;
	}
	return (h);
}

/**
 * free_list - Clears a linked list from memory
 * @head: Pointer to the head of the linked list
 */
void free_list(list_t *head)
{
	list_t *ptr = head;

	while (head)
	{
		ptr = head->next;
		free(head->str);
		free(head->val);
		free(head);
		head = ptr;
	}
}

