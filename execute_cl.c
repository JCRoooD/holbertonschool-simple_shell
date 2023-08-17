#include "header_shell.h"
/**
 * execute_cl - executing a command line given 
 * @command: command given
 * @env: environment variable
 */
void execute_cl(char *command, char **env)
{
	pid_t child_pid;
	char *token = NULL;
	char **tokens = NULL;
	int count = 0;

	token = strtok(command, " \n"); /*tokenize the string*/
	if (token == NULL)
		return;

	while (token != NULL)
	{
		tokens = realloc(tokens, sizeof(char *) * (count + 1));
		if (tokens == NULL)
		{
			perror("realloc");
			return;
		}
		tokens[count] = token;
		count++;
		token = strtok(NULL, " \n");
		tokens[count] = NULL;
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork"); 
		return;
	}
	if (child_pid == 0)
	{
		execve(tokens[0], tokens, env);
		perror("error ");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
		free(tokens);
	}
}
