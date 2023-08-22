#include "shell.h"

#define BUFFER_SIZE 1024

int main(void) {
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t characters_read;

    while (1) {
        printf("$ "); // Prompt
        characters_read = getline(&buffer, &bufsize, stdin);

        if (characters_read == -1) {
            perror("getline");
            exit(EXIT_FAILURE);
        }


        buffer[characters_read - 1] = '\0';

        if (strcmp(buffer, "exit") == 0) {
            free(buffer);
            exit(EXIT_SUCCESS);
        }

        system(buffer);
    }

    return 0;
}
