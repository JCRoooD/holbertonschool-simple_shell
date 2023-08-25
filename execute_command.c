#include "header_shell.h"

/**
 * command_path - Get the full path of a command
 * @command_line: The name of the command
 * Return: A dynamically allocated string containing the full path
 *         NULL if the command is not found
 */
char *command_path(char *command_line)
{
	char *command_path = "/bin/";
	char *entire; /*entire path*/

	if (access(command_line, X_OK) == 0)
	{
		entire = strdup(command_line);
		if (entire == NULL)
		{
			perror("malloc");
			return (NULL);
		}
		return (entire);
	}

	entire = malloc(strlen(command_path) + strlen(command_line) + 1);
	if (entire == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	sprintf(entire, "%s%s", command_path, command_line); /* concat */

	/* Check if the full path is executable */
	if (access(entire, X_OK) != 0)
	{
		perror("Command not found");
		free(entire);
		return (NULL);
	}

	return (entire);
}

/**
 * execute_command - Execute a command using fork and execve
 * @command: The command to execute
 * @env: The environment variables
 */
void execute_command(char *command, char **env)
{
	char *token = NULL;
	char **tokens = NULL;
	int arg_count = 0;
	char *entire;

	token = strtok(command, " \n"); /* Tokenize the command string */
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
		tokens[arg_count] = strdup(token); /* Store token in tokens array */
		arg_count++;						 /* Increment the token count */
		token = strtok(NULL, " \n");		 /* Get next token from command string */
	}
	tokens = realloc(tokens, sizeof(char *) * (arg_count + 1));
	if (tokens == NULL)
	{
		perror("realloc");
		return;
	}
	tokens[arg_count] = NULL; /* Set next element in the array to NULL */

	entire = command_path(tokens[0]); /* Get the full path of the command */
	if (entire == NULL)
	{
		free_token(tokens, arg_count);
		return;
	}

	free(tokens[0]);
	tokens[0] = entire;
	child_process(tokens, env);
	free_token(tokens, arg_count);
}

/**
 * create_child_process - Create a child process and execute the command
 * @tokens: The tokenized command and arguments
 * @env: The environment variables
 */
void child_process(char **tokens, char **env)
{
	pid_t pid = fork(); /* Create a child process */
	int status;

	if (pid == -1)
	{
		perror("fork"); /* Print error message if fork fails */
		return;
	}
	if (pid == 0)
	{
		execve(tokens[0], tokens, env); /* Execute the command using execve */
		perror("error ");				/* Print an error message if execve fails */
		exit(EXIT_FAILURE);				/* Exit child process with failure status */
	}
	else
	{
		/* Wait specifically for the child process to complete */
		waitpid(pid, &status, 0);
	}
}

/**
 * get_paths - Extracts paths from the PATH environment variable
 * Return: A pointer to an array of strings containing the paths
 *         NULL on failure or if PATH is not found
 */
char **get_paths(void)
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
		num_path++;					  /* Increment the num_paths counter. */
		token = strtok(NULL, ":");		  /* Move to the next token */
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
