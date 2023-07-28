#ifndef LISTSH
#define LISTSH

#include <unistd.h>

/**
 * struct list_s - Represents a node in a singly linked list
 * @str: Holds the string data
 * @val: Stores the value of the string data
 * @len: Measures the string length
 * @valLen: Measures the value string length
 * @next: Points to the succeeding node in the list
 *
 * Explanation: This struct typifies a node within a singly linked
 * list, pertinent to the ALX shell project.
 */

typedef struct list_s
{
	char *str;
	char *val;
	unsigned int len;
	unsigned int valLen;
	struct list_s *next;
} list_t;

/* Outputs a single character */
int _putchar(char c);

/* Prints all elements of a list_t list */
size_t print_list(list_t *h);

/* Counts the number of elements in a list_t list */
size_t list_len(list_t *h);

/* Appends a new node at the start of a list_t list */
list_t *add_node(list_t **head, char *str, char *val);

/* Liberates a list_t list */
void free_list(list_t *head);

/* Retrieves a specific node in a list_t list */
list_t *get_node(list_t *head, char *str);

#endif

