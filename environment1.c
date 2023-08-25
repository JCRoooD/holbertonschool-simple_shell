/**
 * main - Remueve todas las variables de entorno excepto una y ejecuta env
 * @argc: Número de argumentos
 * @argv: Argumentos de línea de comandos
 * @envp: Variables de entorno
 * Return: Valor de salida del programa
 */
int main(int argc, char *argv[], char *envp[])
{
    int i;
    char *keep_variable = "VARIABLE"; // Variable a mantener

    // Eliminar todas las variables de entorno excepto la que se desea mantener
    for (i = 0; envp[i] != NULL; i++)
    {
        if (strncmp(envp[i], keep_variable, strlen(keep_variable)) != 0)
        {
            unsetenv(envp[i]);
        }
    }

    // Ejecutar el comando "env" para mostrar las variables de entorno restantes
    if (execvp("env", argv) == -1)
    {
        perror("execvp");
        return EXIT_FAILURE;
    }

    return 0;
}
