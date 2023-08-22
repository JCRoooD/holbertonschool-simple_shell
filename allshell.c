#include "shell.h"

#define MAX_COMMAND_LENGTH 100

void display_prompt() {
    printf("$ ");
}

void execute_command(char *command) {
    if (strcmp(command, "exit") == 0) {
        exit(0);
    }
    else if (strcmp(command, "env") == 0) {
        extern char **environ;
        for (int i = 0; environ[i] != NULL; i++) {
            printf("%s\n", environ[i]);
        }
    }
    else {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(1);
        }
        else if (pid == 0) {
            if (execlp(command, command, (char *)NULL) == -1) {
                perror("execlp");
                exit(1);
            }
        }
        else {
            wait(NULL);
        }
    }
}

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        display_prompt();

        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;
        }

        command[strcspn(command, "\n")] = '\0';

        execute_command(command);
    }

    return 0;
}
