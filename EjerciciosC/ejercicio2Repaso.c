#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#define MAXNUMGEN 20
#define MAXNUMRAND 100

// Declaración de la función esPar
int esPar(int numeroAComprobar);

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    pid_t hijo1;
    pid_t hijo2;
    int pipe_hijo1[2];
    int pipe_hijo2[2];

    if (pipe(pipe_hijo1) != 0)
    {
        printf("El pipe hijo 1 ha fallado");
        return 1;
    }

    if (pipe(pipe_hijo2) != 0)
    {
        printf("El pipe hijo 2 ha fallado");
        return 1;
    }

    for (int i = 0; i < MAXNUMGEN; i++)
    {
        int numeroRandom = 0;
        numeroRandom = rand() % MAXNUMRAND;
        if (esPar(numeroRandom))
        {
            write(pipe_hijo1[1], &numeroRandom, sizeof(int));
        }
        else
        {
            write(pipe_hijo2[1], &numeroRandom, sizeof(int));
        }
    }
    if ((hijo1 = fork()) == 0)
    {
        close(pipe_hijo1[1]);
        int numeroRecibido = 0;
        for (int i = 0; i < MAXNUMGEN; i++)
        {
            read(pipe_hijo1[0], &numeroRecibido, sizeof(int));
            printf("Soy el hijo 1 y he recibido este numero par: %d\n", numeroRecibido);
        }
        fflush(stdout);
        close(pipe_hijo1[0]); 
        return 0;
    }

    if ((hijo2 = fork()) == 0)
    {
        close(pipe_hijo2[1]);
        int numeroRecibido = 0;
        for (int i = 0; i < MAXNUMGEN; i++)
        {
            read(pipe_hijo2[0], &numeroRecibido, sizeof(int));
            printf("Soy el hijo 2 y he recibido este numero impar: %d\n", numeroRecibido);
        }
        fflush(stdout);
        close(pipe_hijo2[0]); 
        return 0;
    }
    return 0;
}

// Definición de la función esPar
int esPar(int numeroAComprobar)
{
    return (numeroAComprobar % 2 == 0);
}

