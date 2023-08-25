#include "header_shell.h"
**/
* execute_command - Execute the command entered by the user
* @command: Command entered by the user
* @env: Environment variables
*/
void execute_command(char *command, char **env)
{
    char *token, **tokens = NULL;
    int arg_count = 0;

    token = strtok(command, " \n");
    while (token != NULL)
    {
        tokens = realloc(tokens, sizeof(char *) * (arg_count + 2));
        tokens[arg_count++] = token;
        token = strtok(NULL, " \n");
    }
    tokens[arg_count] = NULL;

    if (fork() == 0)
    {
        execve(tokens[0], tokens, env);
        perror("Error ");
        exit(EXIT_FAILURE);
    }
    else
    {
        wait(NULL);
        free(tokens);
    }
}
