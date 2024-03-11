#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <strings.h>
#include <math.h>
#define MAXGENNUM 999
#define MINGENNUM 100

int fin = 1;

int esPrimo(int num)
{
    if (num < 2)
        return 0;
    for (int i = 2; i * i <= num; ++i)
    {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

int esMultiploDiez(int numero)
{
    if (numero % 10 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void manejadorSIGUSR1(int signal)
{
    fin = 0;
}

int main(int argc, char const *argv[])
{
    pid_t hijo;
    int pipeHijoPadre[2];
    srand(time(NULL));

    if (pipe(pipeHijoPadre) != 0)
    {
        printf("pipe roto");
        return 1;
    }
    signal(SIGUSR1, manejadorSIGUSR1);
    if ((hijo = fork()) == 0)
    {
        int numeroRecibido = 0;
        int resultado = 0;
        int contador = 0;
        while (fin)
        {
            read(pipeHijoPadre[0], &numeroRecibido, sizeof(int));
            printf("numero recibido por pipe de mi papa: %d\n", numeroRecibido);
            if (esPrimo(numeroRecibido))
            {
                resultado += numeroRecibido;
                contador++;
            }
            if (esMultiploDiez(numeroRecibido))
            {
                kill(getppid(), SIGUSR1);
                write(pipeHijoPadre[1], &resultado, sizeof(int));
                exit(0);
            }
        }
    }
    else
    {
        while (fin)
        {
            int numeroAleatorio = (rand() % MAXGENNUM) + MINGENNUM;
            while (numeroAleatorio > MAXGENNUM)
            {
                numeroAleatorio = (rand() % MAXGENNUM) + MINGENNUM;
            }

            write(pipeHijoPadre[1], &numeroAleatorio, sizeof(int));
            sleep(3);
        }
        waitpid(hijo, NULL, 0);
        int numeroRecibidoHijo = 0;
        read(pipeHijoPadre[0], &numeroRecibidoHijo, sizeof(int));
        printf("la suma que me ha pasado mi hijo es: %d\n", numeroRecibidoHijo);
        close(pipeHijoPadre[0]);
        close(pipeHijoPadre[1]);
    }
}