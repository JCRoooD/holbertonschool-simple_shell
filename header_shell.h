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
/*environment variable*/
extern char **environ;

/*protoypes*/
int main(int ac, char **av, char **env);
void execute_command(char *command, char **env);
void free_token(char **tokens, int arg_count);
void free_path(char **path, int num_path);
void child_process(char **tokens, char **env);
char **get_path(void);
char *trim_digits(char *str);
#endif