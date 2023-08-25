#include "header_shell.h"
/**
 * main - our shell program
 * @ac: argument counter
 * @av: argument vector
 * @env: environment Variables
 * Return: Always 0
 *
 */
int main(int ac, char **av, char **env)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t characters_read;
	int is_interactive = isatty(STDIN_FILENO);
	char *path_variable = get_path(env);


if (isspace((unsigned char)buffer[0]))
			continue;

		if (buffer[0] == '\0' || buffer[0] == ' ')
			continue;
		execute_command(buffer, env);
	}
	if (path_variable)
	{
		printf("the PATH value: %s\n", path_variable);
		free(path_variable);
	}
	free(buffer);
	return (0);
