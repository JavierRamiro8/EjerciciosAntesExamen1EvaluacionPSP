#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <strings.h>
#include <string.h>
#include <math.h>
#define MAXGENNUM 100
#define HIJO1 "HIJO 1"
#define HIJO2 "HIJO 2"

char primerEncontrado[10];

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

void manejador(int signal)
{
    if (signal == SIGUSR1 && strcmp(primerEncontrado, HIJO2) != 0)
    {
        strcpy(primerEncontrado, HIJO1);
    }
    else if (signal == SIGUSR2 && strcmp(primerEncontrado, HIJO1) != 0)
    {
        strcpy(primerEncontrado, HIJO2);
    }
}

int main(int argc, char const *argv[])
{
    /*if (argc != 2)
    {
        printf("argumento invalido");
        return 1;
    }*/
    srand(time(NULL));
    pid_t hijo1;
    pid_t hijo2;
    signal(SIGUSR1, manejador);
    signal(SIGUSR2, manejador);

    int numeroRecibido = 3;
    int pipeHijo1Padre[2];
    int pipeHijo2Padre[2];
    if (pipe(pipeHijo1Padre) != 0)
    {
        printf("pipe roto");
        return 1;
    }
    if (pipe(pipeHijo2Padre) != 0)
    {
        printf("pipe roto");
        return 1;
    }

    write(pipeHijo1Padre[1], &numeroRecibido, sizeof(int));
    write(pipeHijo2Padre[1], &numeroRecibido, sizeof(int));

    if ((hijo1 = fork()) == 0)
    {
        int numeroRecibidoPadre = 0;
        read(pipeHijo1Padre[0], &numeroRecibidoPadre, sizeof(int));
        int numerosAleatoriosHijo1[numeroRecibidoPadre];
        for (int i = 0; i < numeroRecibidoPadre; i++)
        {
            numerosAleatoriosHijo1[i] = rand() % MAXGENNUM;
            printf("Hijo1 con el numero aleatorio:%d en el indice %d\n", numerosAleatoriosHijo1[i], i);
        }
        for (int i = 0; i < numeroRecibidoPadre; i++)
        {
            for (int j = 0; j < numeroRecibidoPadre; j++)
            {
                int resultado = 0;
                resultado = numerosAleatoriosHijo1[i] + numerosAleatoriosHijo1[j];
                if (esPrimo(resultado))
                {
                    kill(getppid(), SIGUSR1);
                }
            }
        }
    }
    else if ((hijo2 = fork()) == 0)
    {
        int numeroRecibidoPadre = 0;
        read(pipeHijo2Padre[0], &numeroRecibidoPadre, sizeof(int));
        int numerosAleatoriosHijo2[numeroRecibidoPadre];
        for (int i = 0; i < numeroRecibidoPadre; i++)
        {
            numerosAleatoriosHijo2[i] = rand() % MAXGENNUM;
            printf("Hijo2 con el numero aleatorio:%d en el indice %d\n", numerosAleatoriosHijo2[i], i);
        }
        for (int i = 0; i < numeroRecibidoPadre; i++)
        {
            for (int j = 0; j < numeroRecibidoPadre; j++)
            {
                int resultado = 0;
                resultado = numerosAleatoriosHijo2[i] + numerosAleatoriosHijo2[j];
                if (esPrimo(resultado))
                {
                    kill(getppid(), SIGUSR2);
                }
            }
        }
    }
    else
    {
        waitpid(hijo1, NULL, 0);
        waitpid(hijo2, NULL, 0);
        if (primerEncontrado[0]=='\0')
        {
            printf("nadie a encontrado ningun primo de la suma de dos primos\n");
        }
        else
        {
            printf("el primero que ha encontrado el primer primo de la suma de dos primos es: %s\n", primerEncontrado);
        }
    }

    return 0;
}
