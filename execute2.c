#include "header_shell.h"

/**
 * execute - execute command line
 * @args: line of arguments
 *
 * Return: 0
 */

int execute(char **args)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("execvp error");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid > 0)
	{
		int status;

		waitpid(pid, &status, 0);
		return (WIFEXITED(status) ? WEXITSTATUS(status) : -1);
	}
	else
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	return (0);
}
