#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, char *argv[])
{

    int numHijos = atoi(argv[1]);
    pid_t hijos[numHijos];

    // Crear n hijos
    for (int i = 0; i < numHijos; i++)
    {
        pid_t child = fork();

        if (child == 0)
        {
            // proceso hijo
            printf("Soy el hijo %d (PID %d) y estoy vivo.\n", i + 1, getpid());
            while (1)
            {

                sleep(1);
            }
        }
        else
        {
            hijos[i] = child;
        }
    }
    sleep(2);

    for (int i = 0; i < numHijos; i++)
    {
        kill(hijos[i], SIGKILL);
        printf("Señal SIGKILL enviada al hijo %d (PID %d)\n", i + 1, hijos[i]);
    }

    // Esperar a que todos los hijos terminen
    for (int i = 0; i < numHijos; i++)
    {
        wait(NULL);
    }

    return 0;
}
