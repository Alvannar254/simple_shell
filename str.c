#include "main.h"


/**
 * strcopy - returns a pointer to a newly allocated space in memory, 
 * @str: pointer to a string
 *
 * Return: pointer to a string
 */

char *strcopy(char *str)
{
	int i, l;
	char *new;

	if (!str)
	{
		return (NULL);
	}
	for (l = 0; str[l] != '\0';)
	{
		l++;
	}
	new = malloc(sizeof(char) * l + 1);
	if (!new)
	{
		return (NULL);
	}
	for (i = 0; i < l; i++)
	{
		new[i] = str[i];
	}
	new[l] = str[l];
	return (new);
}


/**
 * concatstr - concats 3 strings in a newly allocated memory
 * @name: first string
 *
 * Return: pointer to the new string
 */


char *concatstr(char *name, char *sep, char *value)
{
	char *result;
	int l1, l2, l3, i, k;

	l1 = lenofstr(name);
	l2 = lenofstr(sep);
	l3 = lenofstr(value);

	result = malloc(l1 + l2 + l3 + 1);
	if (!result)
		return (NULL);

	for (i = 0; name[i]; i++)
		result[i] = name[i];
	k = i;

	for (i = 0; sep[i]; i++)
		result[k + i] = sep[i];
	k = k + i;

	for (i = 0; value[i]; i++)
		result[k + i] = value[i];
	k = k + i;

	result[k] = '\0';

	return (result);
}

/**
 * lenofstr - it gives the length of a string
 * @stp: pointer to the string
 * Return: the length of string
 */
int lenofstr(char *stp)
{
	int i = 0;

	while (*(stp + i) != '\0')
	{
		i++;
	}
	return (i);
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _puts - prints a string
 * @str: pointer to string
 *
 *exit
 */

void _puts(char *str)
{
	int i = 0;

	while (str[i])
	{
		_putchar(str[i]);
		i++;
	}
}

