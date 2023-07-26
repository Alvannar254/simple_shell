#ifndef MAIN_H
#define MAIN_H

extern char **environ;

char *find_path(char *cmd);
int execute_command(char *line);
char *_getenv(const char *name);
void handle_exit(char **args);
void handle_env(char **args);

#endif /* MAIN_H */

