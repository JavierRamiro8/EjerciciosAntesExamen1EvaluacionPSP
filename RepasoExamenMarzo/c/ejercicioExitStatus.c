#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    

    int num = 23;
    pid_t pid = fork();

    if (pid == 0) {
        // Proceso hijo
        if (num % 2 == 0) {
            exit(0); // Devolver 0 si el número es par
        } else {
            exit(1); // Devolver 1 si el número es impar
        }
    } else if (pid > 0) {
        // Proceso padre
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            if (exit_status == 0) {
                printf("El número %d es par.\n", num);
            } else {
                printf("El número %d es impar.\n", num);
            }
        }
    } else {
        // Error al crear el proceso hijo
        perror("Error al crear el proceso hijo");
        return 1;
    }

    return 0;
}