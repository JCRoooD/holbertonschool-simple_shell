#include "header_shell.h"
/**
 * extract_value - function to extract the value of an environment variable
 * @entry: environment entry
 * Return: NULL
 */
char *extract_value(const char *entry)
{
	const char *equals = strchr(entry, '=');
	if (equals)
	{
		return strdup(equals + 1);
	}
	return (NULL);
}

/**
 * get_path - function that adds the path
 * @env: environment variable
 * Return: always NULL 
 */
char *get_path(char **env)
{
	int i;
    char *path_variable;
    for (i = 0; env[i] != NULL; i++)
    {
        if (strncmp(env[i], "PATH=", 5) == 0)
        {
            path_variable = extract_value(env[i]);
            break;
        }
    }
	return (path_variable);
}
