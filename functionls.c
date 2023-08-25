#include "header_shell.h"

int main()
{
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Proceso hijo
        close(pipefd[1]);  // Cerramos el extremo de escritura del pipe

        // Redirigimos la entrada estándar al extremo de lectura del pipe
        if (dup2(pipefd[0], STDIN_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }

        // Ejecutamos el comando /bin/ls
        if (execl("/bin/ls", "ls", (char *)NULL) == -1) {
            perror("execl");
            exit(EXIT_FAILURE);
        }
    } else {
        // Proceso padre
        close(pipefd[0]);  // Cerramos el extremo de lectura del pipe

        // Escribimos el comando en el extremo de escritura del pipe
        if (write(pipefd[1], "/bin/ls", sizeof("/bin/ls")) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        // Esperamos a que el proceso hijo termine
        wait(NULL);
    }

    return 0;
}
