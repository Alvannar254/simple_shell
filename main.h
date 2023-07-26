#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>

extern char **environ;

char *find_path(char *cmd);
int execute_command(char *line);

#endif /* MAIN_H */

