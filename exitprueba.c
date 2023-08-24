#include "header_shell.h"


int main() {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        char* command = "comando_que_falla"; // Reemplaza esto con el comando que deseas ejecutar y que sabes que fallará
        execlp(command, command, NULL);
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent process
        wait(NULL);
    } else {
        // Fork failed
        printf("Fork failed\n");
    }

    return 0;
}
