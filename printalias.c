#include <stdlib.h>
#include "shell.h"
#include "main.h"
#include "lists.h"

/**
 * print_alias - output the value of a specified alias
 * @name: target alias name to be output
 * @params: parameter structure containing the list of aliases
 *
 * This routine scans the list of aliases in the provided parameter structure
 * searching for the specified alias. If located, value written to stdout.
 * If the alias is not present, an error notification is directed to stderr.
 */
void print_alias(char *name, param_t *params)
{
	unsigned int len = 0;
	list_t *ptr = params->alias_head;

	len = _strlen(name); /* Obtain length of the provided name */
	while (ptr) /* Scan through the alias list */
	{
		if (_strcmp_n(name, ptr->str, len - 1) == 0) /* Match found */
			_printf("%s=\'%s\'\n", ptr->str, ptr->val); /* Output alias */
		ptr = ptr->next; /* Move to next alias in the list */
	}
	params->status = 0; /* Reset status */
}

/**
 * print_all_aliases - display all aliases in the alias list
 * @params: parameter structure encapsulating the list of aliases
 *
 * This routine traverses the alias list in the given parameter structure,
 * writing the name and value of each alias to stdout.
 */
void print_all_aliases(param_t *params)
{
	print_list_alias(params->alias_head); /* Print the whole alias list */
	params->status = 0; /* Reset status */
}

/**
 * print_list_alias - output name and value of each alias in a list
 * @head: pointer to the head of the alias list
 *
 * This routine goes through the list of aliases, outputting the name
 * and value of each alias to stdout.
 */
void print_list_alias(list_t *head)
{
	if (head) /* If the list is not empty */
	{
		print_list_alias(head->next); /* Recursive call to print next alias */
		if (head->str != NULL) /* Ensure alias name is not NULL */
			_printf("%s=\'%s\'\n", head->str, head->val); /* Output alias */
	}
}

