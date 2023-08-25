#include "header_shell.h"
/**
 *execute_command - Ejecuta el comando ingresado por el usuario
 * @command: Comando ingresado por el usuario
 * @env: Variables de entorno
 */
void execute_command(char *command, char **env)
{
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
		tokens[arg_count] = strdup(token);
		if (tokens[arg_count] == NULL)
		{
			perror("strdup");
			free_token(tokens, arg_count);
			return;
		}
		arg_count++;
		token = strtok(NULL, " \n");
	}

	if (tokens == NULL)
	{
		perror("realloc");
		return;
	}
	tokens[arg_count] = NULL;

	free(tokens[0]);
	child_process(tokens, env);
	free_token(tokens, arg_count);
}

/**
 * child_process - function that creates child process
 * @tokens: tokenized command
 * @env: environmental variable
 */
void child_process(char **tokens, char **env)
{
	pid_t pid = fork();
	int status;

	if (pid == -1)
	{
		perror("fork");
		return;
	}
	if (pid == 0)
	{
		execve(tokens[0], tokens, env);
		perror("error ");
		exit(EXIT_FAILURE);
	}
	else
	{
		/* Proceso padre */
		waitpid(pid, &status, 0);
	}
}

/**
 * get_path - function that gets the path environment
 * Return: null if unsuccessful or the path if successful
 */
char **get_path(void)
{
	/* Get the value of the PATH environment variable */
	char *path_variable = getenv("PATH");
	char *token = NULL;
	int num_path = 0;
	char **path = NULL;

	/* Check if PATH environment variable exists */
	if (path_variable == NULL)
	{
		perror("error ");
		return (NULL);
	}

	token = strtok(path_variable, ":");
	while (token != NULL)
	{
		/* Allocate memory for the new path in the array */
		path = realloc(path, sizeof(char *) * (num_path + 1));
		if (path == NULL)
		{
			perror("error ");
			free_path(path, num_path);
			return (NULL);
		}

		path[num_path] = strdup(token); /* Store the current path in the array */
		num_path++;						/* Increment the num_paths counter. */
		token = strtok(NULL, ":");		/* Move to the next token */
	}
	path = realloc(path, sizeof(char *) * (num_path + 1));
	if (path == NULL)
	{
		perror("error ");
		free_path(path, num_path);
		return (NULL);
	}
	path[num_path] = NULL; /* Add NULL pointer at the end of the array */

	free(path_variable); /* Free the environment variable string */
	return (path);
}
