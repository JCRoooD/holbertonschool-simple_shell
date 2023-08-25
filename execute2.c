#include "header_shell.h"
/**
 * execute_command - execute a command
 * @command: command to be executed
 *
 * Return: status
 */

int execute_command(char *command)
{
	int status = -1;
	char *line = strdup(command);
	char **args = tokenize(line);

	if (args[0] != NULL)
	{
		status = execute(args);
		free_args(args);
	}
	free(line);
	return (status);
}
