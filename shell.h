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

void _EOF(int len, char *buff);
void execute(char **argv);
void env(char **arv __attribute__ ((unused)))




extern char **environ;


/**
 *
 */
typedef struct list_path
{
	char *dir;
	struct list_path *p;
} list_path;



typedef struct mybuild
{
	char *name;
	void (*func)(char **);
} mybuild;





#endif
