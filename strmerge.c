#include <stdlib.h>

/**
 * str_concat - Merges two strings into a new string
 * @s1: primary string
 * @s2: string to be appended
 * Return: Null if fails, else memory address to new string
 */
char *str_concat(char *s1, char *s2)
{
	char *ptr;
	int i = 0;
	int j = 0;
	int x = 0;

	s1 = s1 ? s1 : "";
	s2 = s2 ? s2 : "";
	while (s1[i])
	{
		i++;
	}
	while (s2[j])
	{
		j++;
	}
	ptr = malloc((i * sizeof(char)) + (j * sizeof(char)) + 1);
	if (!ptr)
	{
		return (NULL);
	}
	for (i = 0; s1[i]; i++, x++)
	{
		ptr[i] = s1[i];
	}
	for (j = 0; s2[j]; j++, x++)
	{
		ptr[x] = s2[j];
	}
	ptr[x] = '\0';
	return (ptr);
}

/**
 * string_nconcat - Joins two strings with n bytes from second string
 * @s1: initial string
 * @s2: string to be appended
 * @n: bytes from s2
 * Return: Null if fails, else memory address to new string
 */
char *string_nconcat(char *s1, char *s2, unsigned int n)
{
	char *ptr;
	unsigned int i = 0;
	unsigned int j = 0;

	s1 = s1 ? s1 : "";
	s2 = s2 ? s2 : "";
	while (s1[i])
	{
		i++;
	}
	while (s2[j])
	{
		j++;
	}
	if (n > j)
	{
		n = j;
	}
	ptr = malloc(sizeof(char) * (n + i) + 1);
	if (!ptr)
	{
		return (NULL);
	}
	for (i = 0; s1[i]; i++)
	{
		ptr[i] = s1[i];
	}
	for (j = 0; j < n; j++)
	{
		ptr[i + j] = s2[j];
	}
	ptr[i + j] = '\0';
	return (ptr);
}

/**
 * _strlen - Measures a string's length
 * @s: target string
 * Return: 0 if null, else length excluding null byte
 */
int _strlen(char *s)
{
	int len = 0;

	if (!s)
	{
		return (0);
	}
	for (; s[len]; len++)
		;
	return (len);
}

/**
 * _strdup - Duplicates a string to a new memory block
 * @str: input string
 * Return: address to new string, NULL if memory not available
 */
char *_strdup(char *str)
{
	int len = 0;
	char *ptr = NULL;

	if (!str)
	{
		return (NULL);
	}
	while (*str)
	{
		len++;
		str++;
	}
	ptr = (char *) malloc(sizeof(char) * (len + 1));
	if (ptr)
	{
		while (len >= 0)
		{
			*(ptr + len--) = *(str--);
		}
	}
	return (ptr);
}

/**
 * _strchr - Finds a character in a string
 * @s: search area
 * @c: target character
 * Return: address of char found, else NULL
 */
char *_strchr(char *s, char c)
{
	int i = 0;

	while (s[i])
	{
		if (s[i] == c)
		{
			return (&s[i]);
		}
		i++;
	}
	if (c == '\0')
	{
		return (&s[i]);
	}
	return (0);
}

