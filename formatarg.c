#include "main.h"
#include <stdlib.h>
#include <stdarg.h>

/**
 * get_arg - Formats argument as per the specified type.
 *
 * @type: Dictates desired format ('c', 's', 'd', 'i', 'b', 'r', 'R').
 * @...: A variable number of arguments based on type specifier.
 *
 * Function receives a type specifier and variable arguments, returning
 * a formatted string. Supported type specifiers:
 *   - 'c': Character is passed as int, returned as string.
 *   - 's': String is passed as char*, returned as string.
 *   - 'd' or 'i': Integer is passed as int, returned as string.
 *   - 'b': Integer is passed as int, returned as binary string.
 *   - 'r': String is passed as char*, returned as reversed string
 *   - 'R': String is passed as char*, returned as ROT13 string.
 *
 * Return: A dynamic string representation of the argument based on the
 *        type specifier, or NULL for unsupported type specifiers.
 */

char *get_arg(char type, ...)
{
	va_list params; /* Variable argument list */

	/* Initializing params to store the variable arguments */
	va_start(params, type);
	switch (type)
	{
		case 'c':
			/* Character formatting */
			return (get_char(va_arg(params, int)));
		case 's':
			/* String formatting */
			return (get_string(va_arg(params, char*)));
		case 'd':
		case 'i':
			/* Integer formatting */
			return (get_number(va_arg(params, int)));
		case 'b':
			/* Binary formatting */
			return (get_binary(va_arg(params, int)));
		case 'r':
			/* Reversed string formatting */
			return (get_rev(va_arg(params, char *)));
		case 'R':
			/* ROT13 string formatting */
			return (get_rot13(va_arg(params, char *)));
		default:
			/* Handles unsupported type specifiers */
			return (NULL);
	}
}

