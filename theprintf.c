#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include "main.h"

#define BUFFER_SIZE 1024

int flush_buffer(char *buffer, int *index);

int print_arg(char *arg);

void get_type(char *format, int *index);

/**
 * _printf - Outputs formatted text
 * @format: Format directives
 *
 * Description: Similar to printf, outputs formatted text to stdout
 * Return: Count of output characters
 */
int _printf(const char *format, ...)
{
	int high, sum = 0, index = 0;
	char *arg = NULL;
	char buffer[BUFFER_SIZE] = {0};
	va_list params;

	if (!format)
		return (-1);

	if (_strlen((char *)format) == 1 && format[0] == '%')
	{
		return (-1);
	}

	high = 0;
	va_start(params, format);

	while (1)
	{
		/* Checks if the buffer is full and flushes it */
		if (index == BUFFER_SIZE)
		{
			sum += flush_buffer(buffer, &index);
		}

		/* Condition to handle format specifiers */
		if (format[high] == '%')
		{
			get_type((char *)format, &high);
			switch (format[high])
			{
				case 'c':
					buffer[index] = (char) va_arg(params, int);
					index++;
					high++;
					continue;
				case 's':
					arg = get_arg('s', va_arg(params, char*));
					break;
				case 'd':
				case 'i':
					arg = get_arg('d', va_arg(params, int));
					break;
				case 'b':
					arg = get_arg('b', va_arg(params, int));
					break;
				case 'r':
					arg = get_arg('r', va_arg(params, char *));
					break;
				case 'R':
					arg = get_arg('R', va_arg(params, char *));
					break;
				case '%':
					arg = malloc(2);
					arg[0] = '%';
					arg[1] = '\0';
					break;
				case '\0':
					buffer[index] = '%';
					index++;
					continue;
				default:
					arg = malloc(3);
					arg[0] = '%';
					arg[1] = format[high];
					arg[2] = '\0';
			}

			/* Check if argument is valid */
			if (!arg)
			{
				va_end(params);
				free(arg);
				return (-1);
			}

			sum += flush_buffer(buffer, &index);
			sum += print_arg(arg);
			free(arg);
			high++;
		}

		else if (format[high] != '\0')
		{
			buffer[index] = format[high];
			index++;
			high++;
		}

		else
		{
			sum += flush_buffer(buffer, &index);
			va_end(params);
			return (sum);
		}
	}

	return (sum);
}

/**
 * flush_buffer - Flushes the buffer to stdout
 * @buffer: Buffer string
 * @index: Current index of buffer string
 *
 * Description: Flushes the buffer to stdout and reset index
 * Return: Total number of characters printed
 */
int flush_buffer(char *buffer, int *index)
{
	int num = 0;

	num = write(1, buffer, *index);
	*index = BUFFER_SIZE - 1;
	while (*index >= 0)
	{
		buffer[*index] = 0;
		*index -= 1;
	}
	*index = 0;
	return (num);
}

/**
 * print_arg - Prints an argument string
 * @arg: Argument string
 *
 * Description: Outputs the argument string to stdout
 * Return: Number of bytes printed
 */
int print_arg(char *arg)
{
	return (write(1, arg, _strlen(arg)));
}

/**
 * get_type - Fetches type specifier from format string
 * @format: Format string
 * @index: Current index of format string
 *
 * Description: Skips spaces, identifies a specifier, moves index to specifier
 */
void get_type(char *format, int *index)
{
	do {
		*index += 1;
	} while (format[*index] == ' ');
}

