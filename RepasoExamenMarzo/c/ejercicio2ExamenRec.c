#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <strings.h>
#include <math.h>
#define CENTENABASE 100

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

int main(int argc, char const *argv[])
{
    pid_t hijo;
    int numeroHijos = atoi(argv[1]);

    for (int i = 1; i < numeroHijos+1; i++)
    {
        if ((hijo = fork()) == 0)
        {
            int numeroBuscadorPrimerPrimo = CENTENABASE * i + 1;
            int exitPrimo = 0;

            while (1)
            {
                if (esPrimo(numeroBuscadorPrimerPrimo))
                {
                    printf("Hemos encontrado al primo, es el: %d\n", numeroBuscadorPrimerPrimo);
                    exitPrimo = numeroBuscadorPrimerPrimo - CENTENABASE * i;
                    exit(exitPrimo);
                }
                else
                {
                    numeroBuscadorPrimerPrimo++;
                }
            }
        }
        else
        {
            int statusHijoPrimo = 0;
            waitpid(hijo, &statusHijoPrimo, 0);
            if (WIFEXITED(statusHijoPrimo))
            {
                int exit_status = WEXITSTATUS(statusHijoPrimo);
                printf("Salida recibida: %d\n", exit_status);
            }
        }
    }

    return 0;
}