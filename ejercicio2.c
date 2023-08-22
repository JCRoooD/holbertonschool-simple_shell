#include "header_shell.h"
#define BUFFER_SIZE 1024

int main(void) {
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t characters_read;

    while (1) {
        printf("$ "); // Prompt
        characters_read = getline(&buffer, &bufsize, stdin);

        buffer[strcspn(buffer, "\n")] = '\0';

        if (strcmp(buffer, "exit") == 0) {
            free(buffer);
            exit(EXIT_SUCCESS);
        }

        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Proceso hijo
            char *args[] = {buffer, NULL};
            execvp(buffer, args);
            perror("execvp");
            exit(EXIT_FAILURE);
        } else {

            wait(NULL);
        }
    }

    return 0;
}
