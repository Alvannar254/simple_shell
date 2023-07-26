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

char *_getenv(const char *name);
char *find_path(char *cmd);
int execute_command(char *line);
void handle_exit(char **args);
void handle_env(char **args);

#endif /* SHELL_H */

