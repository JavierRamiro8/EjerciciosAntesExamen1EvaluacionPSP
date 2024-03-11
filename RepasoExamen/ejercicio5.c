#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// Función de manejador de señales
void manejadorDeSeñales(int signum)
{
    if (signum == SIGUSR1)
    {
        printf("Señal SIGUSR1 recibida por el hijo. Terminando el proceso hijo.\n");
        exit(0);
    }
}

int main()
{
    pid_t child_pid;
    int status;

    // Establecer el manejador de señales personalizado en el proceso hijo
    signal(SIGUSR1, manejadorDeSeñales);

    child_pid = fork();

    if (child_pid == -1)
    {
        perror("Error al crear el proceso hijo");
        exit(1);
    }

    if (child_pid == 0)
    {
        // Proceso hijo
        printf("Proceso hijo creado (PID %d).\n", getpid());
        while (1)
        {
            // El proceso hijo espera señales continuamente
        }
    }
    else
    {
        // Proceso padre
        printf("Proceso padre (PID %d) creó un proceso hijo (PID %d).\n", getpid(), child_pid);

        // Simular un retraso antes de enviar la señal al hijo
        sleep(2);

        // Enviar una señal SIGUSR1 al proceso hijo
        if (kill(child_pid, SIGUSR1) == -1)
        {
            perror("Error al enviar la señal al hijo");
            exit(1);
        }

        // Esperar a que el hijo termine
        wait(&status);

        printf("Proceso hijo terminado.\n");
    }

    return 0;
}
