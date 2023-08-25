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

	while (1)
	{
		(void)ac;
		(void)av;

		if (is_interactive)
		{
			printf("$ "); /*show prompt*/
		}
		characters_read = getline(&buffer, &bufsize, stdin);
		if (characters_read == -1)
			break;

		buffer[strcspn(buffer, "\n")] = '\0';

		if (strcmp(buffer, "exit") == 0)
			break;
