#include "header_shell.h"
/**
 * main - our shell program
 * @ac: argument counter
 * @av: argument vector
 * @env: environment
 * Return: Always 0
 */
int main(int ac, char **av, char **env)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	ssize_t characters_read;
	int is_interactive = isatty(STDIN_FILENO);
	char *trim;

	while (1)
	{
		if (is_interactive)
		{
			printf("$ "); /*show prompt*/
		}
		(void)ac;
		(void)av;

		characters_read = getline(&buffer, &bufsize, stdin);

		if (characters_read == -1)
			break;

		trim = trim_digits(buffer);

		if (strcmp(trim, "exit") == 0)
			break;

		if (trim[0] == '\0')
			continue;
		execute_command(buffer, env);

		free(buffer);
		buffer = NULL;
	}

	if (buffer != NULL)
		free(buffer);

	return (0);
}

/**
 * trim_digits - Remove leading and trailing digits from a string
 * @str: The string to trim
 * Return: A pointer to the trimmed string
 */
char *trim_digits(char *str)
{
	char *beg = str;					/* Pointer to the start of the string */
	char *last = str + strlen(str) - 1; /* Pointer to the end of the string */

	while (isspace((unsigned char)*beg))
		beg++;

	/* Remove trailing whitespace */
	while (last > beg && isspace((unsigned char)*last))
		last--;

	/* Null-terminate the trimmed string */
	last[1] = '\0';

	return (beg); /* Return the trimmed string */
}
