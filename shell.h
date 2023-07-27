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

extern char **environ;

void(*checkbuild(char **arv))(char **arv);
void exitt(char **arv);
int _atoi(char *s);
void env(char **arv __attribute__ ((unused)));
void _setenv(char **arv);
void _unsetenv(char **arv);
