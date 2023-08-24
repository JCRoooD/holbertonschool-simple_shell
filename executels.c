#include "header_shell.h"

int main() {
    // Obtén el valor de la variable de entorno PATH
    char* path = getenv("PATH");

    // Verifica si el comando "ls" existe en alguna de las rutas del PATH
    char* ls_path = NULL;
    char* token = strtok(path, ":");
    while (token != NULL) {
        char* ls_candidate = malloc(strlen(token) + strlen("/ls") + 1);
        strcpy(ls_candidate, token);
        strcat(ls_candidate, "/ls");
        if (access(ls_candidate, X_OK) == 0) {
            ls_path = ls_candidate;
            break;
        }
        free(ls_candidate);
        token = strtok(NULL, ":");
    }

    // Si se encontró el comando "ls", ejecútalo
    if (ls_path != NULL) {
        pid_t pid = fork();
        if (pid == 0) {
            execl(ls_path, "ls", NULL);
        } else if (pid > 0) {
            wait(NULL);
        } else {
            printf("Error al crear el proceso hijo\n");
        }
    } else {
        printf("El comando 'ls' no existe en tu sistema.\n");
    }

    return 0;
}
