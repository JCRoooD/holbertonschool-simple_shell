#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

#define BUFFER_SIZE 1024

int main(int ac, char **av, char **env)
{
    char *command;
    char *buffer = NULL;
    size_t bufsize = 0;
    pid_t pid;
    int status;

    while (1) {
        printf("$ "); // Mostrar el prompt
        if (getline(&buffer, &bufsize, stdin) == -1) {
            break; // Salir en caso de fin de archivo (Ctrl+D)
        }

        if (buffer[0] == '\n') {
            continue; // Comando vacío, mostrar el prompt de nuevo
        }

        buffer[strcspn(buffer, "\n")] = '\0'; // Eliminar el salto de línea final

        pid = fork(); // Crear un proceso hijo

        if (pid < 0) {
            perror("Error al hacer fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Proceso hijo
            command = buffer;
            execve(command, NULL, environ);
            perror("Error al ejecutar el comando"); // execve solo devuelve si ocurre un error
            exit(EXIT_FAILURE);
        } else {
            // Proceso padre
            waitpid(pid, &status, 0); // Esperar a que el proceso hijo termine
        }
    }

    free(buffer);

    return 0;
}
