#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

/**
 * struct linked_t - singly linked list
 * @str: string - (malloc'ed string)
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct linked_t
{
	char *str;
	struct linked_t *next;
} list_t;

/* Function Prototypes */
char **splitstring(char *line);
int execute_command(char *line);
int exitt(char **args);
int env(char **args);
list_t *linkpath(void);
char *_which(char *cmd, list_t *head);
char *_getenv(const char *name);
list_t *add_node_end(list_t **head, char *str);
char *concat_all(char *str1, char *str2, char *str3);

#endif /* SHELL_H */

