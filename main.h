#ifndef _MAIN_H_
#define _MAIN_H_
#define NULL_PTR -1
#define WRONG_SPECIFIER -2

/**
 * get_char - Allocates a character and a null byte in memory.
 *
 * @c: Input character.
 *
 * Return: Pointer to allocated memory, or NULL on error.
 */
char *get_char(char c);

/**
 * get_string - Stores a string in a malloc'd memory block.
 *
 * @s: Input string.
 *
 * Return: Pointer to the memory block, or NULL on error.
 */
char *get_string(char *s);

/**
 * get_number - Stores an integer in a malloc'd memory block.
 *
 * @n: Input integer.
 *
 * Return: Pointer to the memory block, or NULL on error.
 */
char *get_number(int n);

/**
 * get_arg - Stores an argument in a malloc'd memory block.
 *
 * @type: The type of the argument.
 *
 * Return: Pointer to the memory block, or NULL on error.
 */
char *get_arg(char type, ...);

/**
 * get_binary - Transforms an unsigned int to binary.
 *
 * @n: Input unsigned integer.
 *
 * Return: Pointer to the binary string.
 */
char *get_binary(unsigned int n);

/**
 * get_rev - Reverses a string.
 *
 * @s: Input string.
 * Return: The reversed string.
 */
char *get_rev(char *s);

/**
 * get_rot13 - Encodes a string using rot13.
 *
 * @s: Input string.
 * Return: The encoded string.
 */
char *get_rot13(char *s);

/* Concatenates two strings */
char *str_concat(char *, char *);

/* Concatenates n characters of a string to another string */
char *string_nconcat(char *, char *, unsigned int);

/* Calculates the length of a string */
int _strlen(char *);

/* A simplified printf function */
int _printf(const char *, ...);

/* Locates a character in a string */
char *_strchr(char *s, char c);

/* Converts a string to an integer */
int _atoi(char *s);

/* Compares two strings */
int _strcmp(char *, char *);

/* Compares n characters of two strings */
int _strcmp_n(char *, char *, int n);

#endif

