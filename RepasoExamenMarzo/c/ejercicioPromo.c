#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

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
}

int main(int argc, char const *argv[])
{
    signal(SIGUSR1, manejadorSIGUSR1);
    signal(SIGUSR2, manejadorSIGUSR2);
    signal(SIGINT, manejadorSIGINT);

    pid_t hijo;
    int pipePadreHijo[2];
    int contador = 7;
    int hijoTerminado = 0;

    if (pipe(pipePadreHijo) != 0)
    {
        perror("pipe");
        return 1;
    }
    hijo = fork();

    srand(time(NULL));
    if (hijo == 0)
    {
        // Cierra el extremo de escritura de la tubería en el proceso hijo
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
        while (contador > 0)
        {
            printf("Escriba un número, tiene %d intentos: ", contador);
            scanf("%d", &numeroAElegir);
            write(pipePadreHijo[1], &numeroAElegir, sizeof(int));
            pause();
            contador--;
        }
        waitpid(hijo, NULL, 0);
    }

    return 0;
}
