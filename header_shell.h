#ifndef HEADER_SHELL_H
#define HEADER_SHELL_H
/*libraries*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stddef.h>
#include <ctype.h>
#include <fcntl.h>
#include <stdarg.h>
#include <dirent.h>
#include <signal.h>
#include <sys/stat.h>
#include <stdbool.h>
/*environment variable*/
extern char **environ;

/*buffer*/
#define BUFFER_SIZE 1024
/*protoypes*/
int main(int ac, char **av, char **env);
void execute_command(char *command, char **env);
char *extract_value(const char *entry);
char *get_path(char **env);
int execute_command(char *command);

#endif
