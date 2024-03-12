#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>

#define NUMERO_PARAMETROS 2
bool primo = false;
int primero = 0;
int segundo = 0;

bool esPrimo(int numero)
{
    // Si el número es menor o igual a 1, no es primo
    if (numero <= 1)
    {
        return false;
    }

    // Verificar si el número es divisible por algún otro número diferente de 1 y él mismo
    for (int i = 2; i <= numero / 2; i++)
    {
        if (numero % i == 0)
        {
            return false; // El número no es primo
        }
    }
    return true; // El número es primo
}

void handler_sigurs1(int signo)
{
    if (signo == SIGUSR1)
    {
        if (primero == 0)
        {
            primero = getpid();
        }
        else
        {
            segundo = getpid();
        }
    }
}

void handler_sigurs2(int signo)
{
    if (signo == SIGUSR2)
    {
        if (primero == 0)
        {
            primero = getpid();
        }
        else
        {
            segundo = getpid();
        }
    }
}

int main(int argc, char *argv[])
{
    // Verificar que el número correcto de parámetros fue proporcionado
    /*if (argc != NUMERO_PARAMETROS)
    {
        printf("Uso: ./ejercicioJorge <numero>\n");
        exit(EXIT_FAILURE);
    }*/

    signal(SIGUSR1, handler_sigurs1);
    signal(SIGUSR2, handler_sigurs2);

    int nAleatorios = 3;

    pid_t hijo1, hijo2;

    srand(time(NULL));

    if ((hijo1 = fork()) == 0)
    {
        int numeros[nAleatorios];
        for (int i = 0; i < nAleatorios; i++)
        {
            numeros[i] = rand() % 100 + 1;
            printf("soy hijo 1 con random %d\n", numeros[i]);
        }

        for (int i = 0; i < nAleatorios; i++)
        {
            for (int j = 0; j < nAleatorios; j++)
            {
                if (esPrimo(numeros[i] + numeros[j]))
                {
                    kill(getppid(), SIGUSR1);
                }
            }
        }
    }

    else if ((hijo2 = fork()) == 0)
    {
        srand(time(NULL));
        int numeros[nAleatorios];
        for (int i = 0; i < nAleatorios; i++)
        {
            numeros[i] = rand() % 100 + 1;
            printf("soy hijo 2 con random %d\n", numeros[i]);
        }

        for (int i = 0; i < nAleatorios; i++)
        {
            if (esPrimo(numeros[i] + numeros[i + 1]))
            {
                kill(getppid(), SIGUSR2);
                exit(EXIT_SUCCESS);
            }
        }
        exit(EXIT_SUCCESS);
    }
    else
    {

        waitpid(hijo1, NULL, 0);
        waitpid(hijo2, NULL, 0);

        if (primero == hijo1)
        {
            printf("1º en encontrar primo: Hijo 1\n");
        }
        else if (primero == hijo2)
        {
            printf("1º en encontrar primo: Hijo 2\n");
        }
        else if(segundo==hijo1){
            printf("2º en encontrar primo: Hijo 1\n");

        }else if(segundo==hijo2){
            printf("2º en encontrar primo: Hijo 1\n");
        }else{
            printf("No se han encontrado primos\n");
        }
    }

    // Aqui va el codigo del padre
}