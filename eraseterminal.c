/* This file includes main.h and shell.h libraries */
#include "main.h"
#include "shell.h"

/**
 * _clear - Erases the contents currently displayed on terminal.
 * @params: User-provided parameters, not used in this function.
 *
 * Return: Does not return a value.
 */
void _clear(param_t *params)
{
	/* Parameter is unused in this function, casting to void */
	(void)params;

	/* Prints escape sequence */
	_printf("\033[2J\033[1;1H");
}

