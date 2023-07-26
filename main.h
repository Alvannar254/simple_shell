#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <stddef.h>
#include <sys/stat.h>
#include <signal.h>

int _putchar(char c);
void _puts(char *str);
int lenofstr(char *stp);
char *strcopy(char *str);
char *concatstr(char *name, char *sep, char *value);

char **spltstr(char *str, const char *delimit);
void commexec(char **argarr);
void *relmem(void *prevptr, unsigned int oldptrsize, unsigned int newptrsize);


extern char **environ;

/**
 * struct list_path - Linked list containing PATH directories
 * @dir: directory in path
 * @p: pointer to next node
 */
typedef struct list_path
{
	char *dir;
	struct list_path *p;
} list_path;


char *_getenv(const char *name);

list_path *addnodeendstr(list_path **head, char *str);

list_path *listpathdr(char *path);
char *pathnamefile(char *filename, list_path *head);

/**
 * struct mbuild - pointer to function with corresponding buildin command
 * @name: buildin command
 * @func: execute the buildin command
 */
typedef struct mbuild
{
	char *name;
	void (*func)(char **);
} mbuild;

void(*chbuildin(char **wordarr))(char **wordarr);


int strtoint(char *stp);
void shellexit(char **wordarr);
void currenv(char **wordarr);
void newenv(char **wordarr);
void rmenv(char **wordarr);

void freewordarr(char **wordarr);
void freelist_t(list_path *head);


#endif

