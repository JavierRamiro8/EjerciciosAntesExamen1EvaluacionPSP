#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int acierto = 0;

void manejadorSIGUSR1(int signal)
{
    printf("Es mas grande el numero\n");
}

void manejadorSIGUSR2(int signal)
{
    printf("Es mas pequeño el numero\n");
}

void manejadorSIGINT(int signal)
{
    printf("Acertaste!!\n");
    fflush(stdout);
}

void manejadorAcierto(int signal)
{
    printf("El padre ha adivinado el número antes de agotar los intentos\n");
    acierto = 1;
}

int main(int argc, char const *argv[])
{
    signal(SIGUSR1, manejadorSIGUSR1);
    signal(SIGUSR2, manejadorSIGUSR2);
    signal(SIGINT, manejadorSIGINT);
    signal(SIGIO, manejadorAcierto);

    pid_t hijo;
    int pipePadreHijo[2];
    int contador = 7;

    if (pipe(pipePadreHijo) != 0)
    {
        perror("pipe");
        return 1;
    }

    hijo = fork();

    if (hijo == 0)
    {
        srand(time(NULL));
        int numeroAleatorio = 77;
        close(pipePadreHijo[1]);

        int numeroRecibido = 0;

        while (contador > 0)
        {
            read(pipePadreHijo[0], &numeroRecibido, sizeof(numeroRecibido));
            if (numeroRecibido < numeroAleatorio)
            {
                kill(getppid(), SIGUSR1);
            }
            else if (numeroRecibido > numeroAleatorio)
            {
                kill(getppid(), SIGUSR2);
            }
            else
            {
                kill(getppid(), SIGINT);
                kill(getppid(), SIGIO);
                exit(0);
            }
            contador--;
        }

        close(pipePadreHijo[0]);
        exit(0);
    }
    else
    {
        close(pipePadreHijo[0]);
        int numeroAElegir = 0;

        while (contador > 0 && !acierto)
        {
            printf("Escriba un número, tiene %d intentos: ", contador);
            scanf("%d", &numeroAElegir);
            write(pipePadreHijo[1], &numeroAElegir, sizeof(int));

            // Agregar un pequeño retardo para permitir que se manejen las señales
            usleep(100); // 100ms

            contador--;
        }

        if (!acierto)
        {
            printf("Se han agotado los intentos sin adivinar el número\n");
        }

        waitpid(hijo, NULL, 0);
    }

    return 0;
}
