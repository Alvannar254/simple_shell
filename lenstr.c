#include "shell.h"



/**
 * _strlen - it gives the length of a string
 * @s: pointer to the string
 * Return: the length of string
 */
int _strlen(char *s)
{
	int i = 0;

	while (*(s + i) != '\0')
	{
		i++;
	}
	return (i);
}
