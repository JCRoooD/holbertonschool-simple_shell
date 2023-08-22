#include "shell.h"
/**
 *execute_command - Ejecuta el comando ingresado por el usuario
 *@command: Comando ingresado por el usuario
 *@env: Variables de entorno
 */
void execute_command(char *command, char **env)
{
pid_t pid;
char **tokens = NULL;
int arg_count = 0;

char *token = strtok(command, " \n");
if (token == NULL)
return;
	while (token != NULL)
{
	tokens = realloc(tokens, sizeof(char *) * (arg_count + 1));
	if (tokens == NULL)
	{
	perror("realloc");
	return;
	}
	tokens[arg_count] = token;
	arg_count++;
	token = strtok(NULL, " \n");
	tokens[arg_count] = NULL;
}
pid = fork();
if (pid == -1)
{
	perror("fork");
}
if (pid == 0)
{

	execve(tokens[0], tokens, env);
	perror("Error ");
	/* execve devuelve si ocurre un error */
	exit(EXIT_FAILURE);
}
else
{
	/* Proceso padre */
	wait(NULL); /* Esperar a que el proceso hijo termine */
	free(tokens);
}
}

int main() {
    char *command = NULL;
    size_t bufsize = 0;
    char *env[] = {NULL}; // Variables de entorno vacías

    printf(" ");
    getline(&command, &bufsize, stdin);
    command[strcspn(command, "\n")] = '\0';

    execute_command(command, env);

    free(command);
    return 0;
}
