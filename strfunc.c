#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include "shell.h"
#include "main.h"

/**
 * _strcpy - Transfers a string to another memory location
 * @src: Origin string pointer
 * @dest: Destination memory location pointer
 *
 * Return: Pointer to the destination
 */
char *_strcpy(char *dest, const char *src)
{
	int i = 0;

	while (src[i] != '\0') /* Copy each character from source to destination */
	{
		dest[i] = src[i];
		i++;
	}

	if (src[i] == '\n') /* Check for newline character */
		dest[i] = '\n';
	return (dest);
}

/**
 * _strcmp - Evaluates string equality
 * @s1: String 1
 * @s2: String 2
 *
 * Return: Integer indicating relation between s1 and s2
 */
int _strcmp(char *s1, char *s2)
{
	int res = 0;

	do {
		res = *s1 - *s2; /* Get the difference of the ASCII values */
		if (*s1 == 0 || *s2 == 0) /* Check for end of string */
			break;
		s1++;
		s2++;
	} while (res == 0);

	return (res);
}

/**
 * _strcmp_n - Compare n bytes of two strings
 * @s1: String 1
 * @s2: String 2
 * @n: Bytes count for comparison
 *
 * Return: Int showing relation between s1 and s2 for first n bytes
 */
int _strcmp_n(char *s1, char *s2, int n)
{
	int i = 0, res = *s1 - *s2;

	while (i <= n)
	{
		res = *(s1++) - *(s2++); /* Compare n bytes of s1 and s2 */
		if (res != 0) /* If they aren't equal, break */
			break;
		i++;
	}

	return (res);
}


/**
 * _atoi - Convert a string to integer
 * @s: String to be converted
 *
 * Return: n as the integer value of the string, -1 for overflow
 */
int _atoi(char *s)
{
	int n = 0, tmp = 0, len, mul = 1;

	len = _strlen(s); /* Length of the string */
	len--;
	while (len >= 0)
	{
		tmp = n;
		n = n + (s[len] - '0') * mul; /* Calculate number from char */
		if (n < tmp || n > INT_MAX) /* Check for overflow */
			return (-1);
		len--;
		mul *= 10;
	}
	return (n);
}

