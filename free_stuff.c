#include "header_shell.h"
/**
 * free_token - free the memory of the array token
 * @tokens: array to free
 * @arg_count: number of tokens
 */
void free_token(char **tokens, int arg_count)
{
	int a;

	for (a = 0; a < arg_count; a++)
	{
		free(tokens[a]);
	}
	free(tokens);
}

/**
 * free_path - frees memory in the path array
 * @path: path array to be freed
 * @num_path: number of paths
 */
void free_path(char **path, int num_path)
{
	int a;

	for (a = 0; a < num_path; a++)
	{
		free(path[a]);
	}
}
