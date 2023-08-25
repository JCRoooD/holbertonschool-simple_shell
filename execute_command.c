#include "header_shell.h"
/**
 * execute_command - Ejecuta el comando ingresado por el usuario
 * @command: Comando ingresado por el usuario
 * @env: Variables de entorno
 */

#include "header_shell.h"

void execute_command(char *command, char **env)
{
pid_t pid;
char *token, **tokens = NULL;
int arg_count = 0;

token = strtok(command, " \n");
while (token != NULL)
{
    tokens = realloc(tokens, sizeof(char *) * (arg_count + 1));
    tokens[arg_count++] = token;
    token = strtok(NULL, " \n");
    tokens[arg_count] = NULL;
}

pid = fork();
if (pid == -1)
{
    perror("fork");
    return;
}
if (pid == 0)
{
    execve(tokens[0], tokens, env);
    perror("Error ");
    exit(EXIT_FAILURE);
    }
    else
    {
        wait(NULL);
        free(tokens);
    }
}
