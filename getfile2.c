#include "main.h"
#include <stdlib.h>

/**
 * rev_string - Inverts character sequence in a string.
 * @s: A pointer to a null-terminated string for inversion.
 */
void rev_string(char *s)
{
	int head, tail;
	int len;
	char tmp;

	/* Handle null string by replacing it with "(null)" */
	if (s == NULL)
	{
		s = "(null)";
	}

	/* Calculate the length of the string */
	for (len = 0; s[len] != '\0'; len++)
		;
	head = 0;
	tail = len - 1;

	/* Swap characters from the start and end of the string */
	while (head < tail)
	{
		tmp = *(s + head);
		*(s + head) = *(s + tail);
		*(s + tail) = tmp;
		head++;
		tail--;
	}
}

/**
 * get_rev - Produces a reversed version of the input string.
 * @s: Input string to reverse.
 * Return: Inverted string.
 */
char *get_rev(char *s)
{
	char *ptr = NULL;

	/* Get a copy of the input string */
	ptr = get_string(s);
	if (!ptr)
	{
		return (NULL);
	}
	if (s)
	{
		/* Reverse the copied string */
		rev_string(ptr);
	}

	return (ptr);
}

/**
 * rot13 - Implements the rot13 cipher on a string.
 * @s: String to encrypt.
 * Return: A pointer to the encrypted string.
 */
char *rot13(char *s)
{
	char *ptr;
	int i;

	/* Character mapping for rot13 cipher */
	char c[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
		'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
		'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
		'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
		'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

	/* Rot13 cipher replacement mapping */
	char r[] = {'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
		'y', 'z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
		'j', 'k', 'l', 'm', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
		'U', 'V', 'W', 'X', 'Y', 'Z', 'A', 'B', 'C', 'D', 'E',
		'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M'};

	/* Perform the rot13 cipher replacement */
	for (ptr = s; *ptr != '\0'; ptr++)
	{
		for (i = 0; i < 52; i++)
		{
			if (*ptr == c[i])
			{
				*ptr = r[i];
				break;
			}
		}
	}

	return (s);
}

/**
 * get_rot13 - Provides the rot13 cipher of the string.
 * @s: String input.
 * Return: Rot13 ciphered string.
 */
char *get_rot13(char *s)
{
	char *ptr = NULL;

	/* Get a copy of the string */
	ptr = get_string(s);
	if (!ptr)
		return (NULL);
	if (s)
	{
		/* Perform rot13 cipher on the copied string */
		rot13(ptr);
	}

	return (ptr);
}

