/*Ejercicio. C. Sincronización de Eventos con Señales

En este ejercicio, vamos a trabajar con un proceso padre y dos procesos hijos.

El padre recibe como parámetro un número n, este número indica la cantidad de número aleatorios que generarán.

Cada hijo genera esos n números (Esa información ya la tienen los hijos), cada proceso hijo se encarga de buscar dos números de esos aleatorios que cuando se sumen den como resultado un número primo.

En cuanto un hijo encuentre un primo le manda una señal al padre hijo1 USR1, hijo2 USR2.

Uno hijo puede que encuentre un número primo o no.

El padre espera a que terminen los procesos y escribe quién ha encontrado el primer primo, quién el segundo o si no han encontrado ninguno.*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#define NUMEROMAXGEN 100

int contadorHijo1 = 0;
int contadorHijo2 = 0;

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

void controladorSignal1()
{
    contadorHijo1++;
    printf("Hijo 1: Se encontró un número primo.\n");
}

void controladorSignal2()
{
    contadorHijo2++;
    printf("Hijo 2: Se encontró un número primo.\n");
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    int numeroRecibido = 0;
    printf("Introduce un numero: ");
    scanf("%d", &numeroRecibido);

    signal(SIGUSR1, controladorSignal1);
    signal(SIGUSR2, controladorSignal2);
    int pipeHijo1[2];
    if (pipe(pipeHijo1) != 0)
    {
        printf("No ha funcionado el pipe hijo1");
        return 1;
    }
    int pipeHijo2[2];
    if (pipe(pipeHijo2) != 0)
    {
        printf("No ha funcionado el pipe hijo2");
        return 1;
    }

    contadorHijo1 = 0;
    contadorHijo2 = 0;

    write(pipeHijo1[1], &numeroRecibido, sizeof(int));
    write(pipeHijo2[1], &numeroRecibido, sizeof(int));

    pid_t hijo1 = fork();
    pid_t hijo2 = fork();

    if (hijo1 == 0)
    {
        close(pipeHijo1[0]);
        int numerosGenerados[numeroRecibido];
        for (int i = 0; i < numeroRecibido; i++)
        {
            numerosGenerados[i] = rand() % NUMEROMAXGEN;
        }
        for (int i = 0; i < numeroRecibido - 1; i++)
        {
            for (int j = i + 1; j < numeroRecibido; j++)
            {
                int numeroComprobarPrimo = numerosGenerados[i] + numerosGenerados[j];
                if (esPrimo(numeroComprobarPrimo))
                {
                    kill(getppid(), SIGUSR1);
                }
            }
        }
        close(pipeHijo1[1]);
        exit(0);
    }
    else if (hijo2 == 0)
    {
        close(pipeHijo2[0]);
        int numerosGenerados[numeroRecibido];
        for (int i = 0; i < numeroRecibido; i++)
        {
            numerosGenerados[i] = rand() % NUMEROMAXGEN;
        }
        for (int i = 0; i < numeroRecibido - 1; i++)
        {
            for (int j = i + 1; j < numeroRecibido; j++)
            {
                int numeroComprobarPrimo = numerosGenerados[i] + numerosGenerados[j];
                if (esPrimo(numeroComprobarPrimo))
                {
                    kill(getppid(), SIGUSR2);
                }
            }
        }
        close(pipeHijo2[1]);
        exit(0);
    }
    else
    {
        waitpid(hijo1, NULL, 0);
        waitpid(hijo2, NULL, 0);
        printf("Número de primos encontrados por el Hijo 1: %d\n", contadorHijo1);
        printf("Número de primos encontrados por el Hijo 2: %d\n", contadorHijo2);
    }

    return 0;
}
