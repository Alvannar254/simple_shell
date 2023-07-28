/* Import required libraries */
#include <stdlib.h>
#include "shell.h"
#include "main.h"

/**
 * isDelim - Identifies if a character is a delimiter
 * @c: The character to be checked
 * @delim: List of delimiters
 *
 * Return: Returns 1 if character is a delimiter, 0 if not
 */
int isDelim(char c, char *delim)
{
	/* Iterate through delimiters */
	while (*delim)
	{
		/* If character is a delimiter, return 1 */
		if (c == *delim)
			return (1);
		delim++;
	}
	/* If character is not a delimiter, return 0 */
	return (0);
}

/**
 * _strtok - Implementation of strtok_r function
 * @str: String to be tokenized
 * @delim: Token delimiters
 * @savePtr: Stores the string state across calls
 *
 * Return: Returns the next token found, NULL if none are found
 */
char *_strtok(char *str, char *delim, char **savePtr)
{
	char *ptr, *modifier, *end;
	int quoteFound = 0;

	/* Initiate pointer based on the savePtr state */
	if (*savePtr)
		ptr = *savePtr;
	else
		ptr = str;

	/* End pointer is set to end of string */
	end = ptr;
	while (*end)
		end++;

	/* Skip leading delimiters */
	while (*ptr && isDelim(*ptr, delim))
		ptr++;

	modifier = ptr;

	/* If the pointer is at end of string, return NULL */
	if (*ptr == '\0')
	{
		return (NULL);
	}

	/* If a quote is encountered, tokenize until the next quote */
	if (*ptr == '\'')
	{
		ptr++;
		modifier = _strchr(ptr, '\'');
		/* If there's no closing quote, output error and exit */
		if (!modifier)
		{
			_printf("no matching quote found!\n");
			exit(-1);
		}
		*modifier = '\0';
		*savePtr = modifier + 1;
		return (_strdup(ptr));
	}

	/* Tokenize until delimiter, skipping anything inside quotes */
	while (*modifier)
	{
		if (*modifier == '\'')
			quoteFound = 1;
		if (isDelim(*modifier, delim) && quoteFound == 0)
			break;
		modifier++;
	}

	/* Set savePtr to next token or to end of string */
	if (*modifier == '\0')
		*savePtr = modifier;
	else
		*savePtr = modifier + 1;

	*modifier = '\0';

	/* Return a duplicate of the token */
	return (_strdup(ptr));
}

