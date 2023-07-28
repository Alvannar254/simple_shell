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
	while (*delim)
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

/**
 * skip_leading_delims - Skips leading delimiters in a string
 * @ptr: Pointer to the string
 * @delim: Delimiters
 *
 * Return: Pointer to the string after skipping leading delimiters
 */
char *skip_leading_delims(char *ptr, char *delim)
{
	while (*ptr && isDelim(*ptr, delim))
		ptr++;
	return (ptr);
}

/**
 * handle_quote_token - Handles tokenization when a quote is encountered
 * @ptr: Pointer to the string
 * @savePtr: Stores the string state across calls
 *
 * Return: Duplicated string of the token if quote is encountered.
 */
char *handle_quote_token(char *ptr, char **savePtr)
{
	char *modifier = NULL;

	if (*ptr == '\'')
	{
		ptr++;
		modifier = _strchr(ptr, '\'');
		if (!modifier)
		{
			_printf("no matching quote found!\n");
			exit(-1);
		}
		*modifier = '\0';
		*savePtr = modifier + 1;
		return (_strdup(ptr));
	}
	return (NULL);
}

/**
 * tokenize_until_delim - Tokenizes until delimiter.
 * @ptr: Pointer to the string
 * @delim: Delimiters
 * @savePtr: Stores the string state across calls
 *
 * Return: Duplicated string of the token
 */
char *tokenize_until_delim(char *ptr, char *delim, char **savePtr)
{
	char *modifier = ptr;
	int quoteFound = 0;

	while (*modifier)
	{
		if (*modifier == '\'')
			quoteFound = 1;
		if (isDelim(*modifier, delim) && quoteFound == 0)
			break;
		modifier++;
	}

	if (*modifier == '\0')
		*savePtr = modifier;
	else
		*savePtr = modifier + 1;

	*modifier = '\0';

	return (_strdup(ptr));
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
	char *ptr, *end;
	char *quoteToken = NULL;

	if (*savePtr)
		ptr = *savePtr;
	else
		ptr = str;

	end = ptr;
	while (*end)
		end++;

	ptr = skip_leading_delims(ptr, delim);

	if (*ptr == '\0')
	{
		return (NULL);
	}

	quoteToken = handle_quote_token(ptr, savePtr);
	if (quoteToken != NULL)
	{
		return (quoteToken);
	}

	return (tokenize_until_delim(ptr, delim, savePtr));
}

