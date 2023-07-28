#ifndef MY_SHELL_H
#define MY_SHELL_H
#define _GNU_SOURCE
#include <stdio.h>
#include "lists.h"

/**
 * struct param_s - Keeps necessary shell variables
 * @argv: Primary command line argument
 * @buffer: User input buffer
 * @args: Parsed arguments array
 * @nextCommand: Subsequent command to execute
 * @argsCap: Capacity of args array
 * @lineCount: Input lines count
 * @tokCount: Count of tokens in a single line
 * @status: Status after executing a command
 * @env_head: Environment variables list
 * @alias_head: List of aliases
 * Description: Maintains variables used in different functions.
 */
typedef struct param_s
{
	char **argv;
	char *buffer;
	char **args;
	char *nextCommand;
	unsigned int argsCap;
	unsigned int lineCount;
	unsigned int tokCount;
	int status;
	list_t *env_head;
	list_t *alias_head;
} param_t;

/**
 * struct op - Inbuilt function type
 * @name: Function name
 * @func: Function pointer
 * Description: Maps function names to their addresses.
 */
typedef struct op
{
	char *name;
	void (*func)(param_t *);
} op_t;

/* Processes input string */
int process_string(param_t *);

/* Duplicates string */
char *_strdup(char *);

/* Copies string */
char *_strcpy(char *dest, const char *src);

/* Reads a line from input */
int _getline(param_t *);

/* Compares two strings */
int _strcmp(char *, char *);

/* Compares 'n' characters of two strings */
int _strcmp_n(char *, char *, int n);

/* Splits a string into tokens */
char *_strtok(char *str, char *delim, char **savePtr);

/* Executes a command */
void run_command(param_t *);

/* Reallocates memory */
void *_realloc(char **ptr, unsigned int old_size, unsigned int new_size);

/* Prints environment variables */
void _printenv(param_t *);

/* Signal handler for SIGINT */
void sigint_handler(int);

/* Retrieves the value of a given environment variable */
char *_getenv(char *name, param_t *params);

/* Sets an environment variable */
void _setenv(param_t *params);

/* Unsets an environment variable */
void _unsetenv(param_t *params);

/* Retrieves the path of a file */
char *get_file(param_t *params);

/* Gets the inbuilt function for execution */
void (*get_builtin(param_t *params))(param_t *);

/* Handles exit function */
void _myExit(param_t *params);

/* Handles cd function */
void _cd(param_t *params);

/* Handles alias function */
void _alias(param_t *params);

/* Sets an alias */
void set_alias(char *name, param_t *params);

/* Creates an alias */
void make_alias(char *name, char *val, param_t *params);

/* Prints a specified alias */
void print_alias(char *name, param_t *params);

/* Prints all available aliases */
void print_all_aliases(param_t *params);

/* Prints environment variables list */
void print_list_env(list_t *);

/* Prints list of aliases */
void print_list_alias(list_t *);

/* Frees resources allocated for parameters */
void free_params(param_t *params);

/* Writes an error message */
void write_error(param_t *params, char *msg);

/* Clears the terminal */
void _clear(param_t *params);
#endif

