

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

void handlePath(char* command, char* path) {
    char* token;
    char* pathCopy = strdup(path);
    char* pathToken = strtok(pathCopy, ":");

    while (pathToken != NULL) {
        char* fullPath = malloc(strlen(pathToken) + strlen(command) + 2);
        sprintf(fullPath, "%s/%s", pathToken, command);

        if (access(fullPath, X_OK) == 0) {
            strcpy(command, fullPath);
            free(fullPath);
            break;
        }

        free(fullPath);
        pathToken = strtok(NULL, ":");
    }

    free(pathCopy);
}

void removeLeadingTrailingSpaces(char* str) {
    int start = 0;
    while (str[start] == ' ') {
        start++;
    }

    int end = strlen(str) - 1;
    while (end >= 0 && str[end] == ' ') {
        end--;
    }

    int length = end - start + 1;
    memmove(str, str + start, length);
    str[length] = '\0';
}

void removeEmptyLines(char* str) {
    char* source = str;
    char* target = str;

    int isPrevNewLine = 0;
    while (*source != '\0') {
        if (*source == '\n') {
            if (!isPrevNewLine) {
                *target++ = *source;
            }
            isPrevNewLine = 1;
        } else {
            *target++ = *source;
            isPrevNewLine = 0;
        }
        source++;
    }
    *target = '\0';
}

void executeCommand(char** arguments) {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        execv(arguments[0], arguments);
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent process
        wait(NULL);
    } else {
        // Fork failed
        printf("Fork failed\n");
    }
}

int main() {
    char command[MAX_COMMAND_LENGTH];
    char* arguments[MAX_ARGUMENTS];

    while (1) {
        printf("Shell > ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "exit") == 0) {
            break;
        }

        // Parse command and arguments
        char* token = strtok(command, " ");
        int i = 0;
        while (token != NULL && i < MAX_ARGUMENTS - 1) {
            arguments[i] = token;
            token = strtok(NULL, " ");
            i++;
        }
        arguments[i] = NULL;

        // Handle the PATH
        char* path = getenv("PATH");
        if (path != NULL) {
            handlePath(arguments[0], path);
        }

        // Remove leading and trailing spaces from arguments
        for (int j = 0; j < i; j++) {
            removeLeadingTrailingSpaces(arguments[j]);
        }

        // Remove empty lines from arguments
        removeEmptyLines(arguments[0]);

        // Execute the command
        executeCommand(arguments);
    }

    return 0;
}
