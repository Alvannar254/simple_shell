#include "main.h"
#include "lists.h"
#include "shell.h"

/**
 * _printenv - Exhibits the environmental variables
 * @params: User parameters
 *
 * Displays all the environment variables in params->env_head.
 * Prints an error in case no environment variables are present.
 *
 * Return: none
 */
void _printenv(param_t *params)
{
	/* If token count is not 1, print error message and set status to 2 */
	if (params->tokCount != 1)
	{
		_printf("env: %s: No such file or directory\n",
				params->args[1]);
		params->status = 2;
		return;
	}
	/* If token count is 1, print environment list and set status to 0 */
	print_list_env(params->env_head);
	params->status = 0;
}

/**
 * print_list_env - Exhibits the environmental variables
 * @head: Head of the environment list
 *
 * Using a pointer to the start of the environment list, it
 * recursively displays the list in reverse. Checks if the str
 * field is not NULL for each list node, then prints the variable
 * name and its corresponding value in "name=value" format.
 */
void print_list_env(list_t *head)
{
	/* If head is not NULL, recursively print the list and check for string */
	if (head)
	{
		print_list_env(head->next);
		/* If str is not NULL, print the variable name and value */
		if (head->str)
			_printf("%s=%s\n", head->str, head->val);
	}
}

