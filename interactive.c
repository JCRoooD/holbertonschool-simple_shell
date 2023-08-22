#include "shell.h"

void execute_command(char *command, char **env) {
    // Resto del código de la función execute_command sin cambios
}

int main() {
    char *command = NULL;
    size_t bufsize = 0;
    char *env[] = {NULL}; // Variables de entorno vacías

    if (isatty(fileno(stdin))) {
        printf("$ ");
    }

    getline(&command, &bufsize, stdin);
    command[strcspn(command, "\n")] = '\0';

    execute_command(command, env);

    free(command);
    return 0;
}
