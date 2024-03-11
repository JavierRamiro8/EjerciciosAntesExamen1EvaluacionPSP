#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>

void manejadorSIGUSR1(int signal)
{
    printf("hola soy el hijo %d y he sido creado\n", getpid());
}
void manejadorSIGUSR2(int signal)
{
    printf("hola soy el hijo %d y he recibido la señal SIGUSR2\n", getpid());
}

int main(int argc, char const *argv[])
{
    int numeroHijos = atoi(argv[1]);
    pid_t arrayHijos[numeroHijos];
    for (int i = 0; i < numeroHijos; i++)
    {
        arrayHijos[i] = fork();
        if (arrayHijos[i] == 0)
        {
            signal(SIGUSR1, manejadorSIGUSR1);
            signal(SIGUSR2, manejadorSIGUSR2);
            pause();
            pause();
            exit(0);
        }
    }

    for (int i = 0; i < numeroHijos; i++)
    {
        kill(arrayHijos[i], SIGUSR1);
    }
    sleep(1);
    for (int i = 0; i < numeroHijos; i++)
    {
        kill(arrayHijos[i], SIGUSR2);
    }
    sleep(1);
    for (int i = 0; i < numeroHijos; i++)
    {
        waitpid(arrayHijos[i], NULL, 0);
    }
    return 0;
}
