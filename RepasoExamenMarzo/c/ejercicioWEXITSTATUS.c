/*
Crea un programa que reciba por parámetro dos números grandes.
El programa creará dos procesos hijos.
Cada hijo gestionará un número primo y verificará si es primo o no.
Cada hijo al finalizar indica en su estado si el número era primo o no.
el proceso padre al recoger el estado del hijo cuenta si era primo o no.
el padre escribe el total de números primos.
*/

/*atoi(argv[1])*/

/*if(argc!=3){
        printf("argumentos insuficientes\n");
        return 1;
    }*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

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
    if(argc!=3){
        printf("argumentos insuficientes\n");
        return 1;
    }

    int numero1 = atoi(argv[1]);
    int numero2 = atoi(argv[2]);

    pid_t hijo1;
    pid_t hijo2;

    int pipePadreHijo1[2];
    int pipePadreHijo2[2];

    if (pipe(pipePadreHijo1) != 0)
    {
        printf("Pipe roto pipePadreHijo1");
    }

    if (pipe(pipePadreHijo2) != 0)
    {
        printf("Pipe roto pipePadreHijo2");
    }

    write(pipePadreHijo1[1], &numero1, sizeof(int));
    write(pipePadreHijo2[1], &numero2, sizeof(int));

    if ((hijo1 = fork()) == 0)
    {
        close(pipePadreHijo1[1]);
        int numeroRecibido = 0;
        read(pipePadreHijo1[0], &numeroRecibido, sizeof(int));
        if (esPrimo(numeroRecibido))
        {
            exit(0);
        }
        else
        {
            exit(1);
        }
    }
    else if ((hijo2 = fork()) == 0)
    {
        close(pipePadreHijo2[1]);
        int numeroRecibido = 0;
        read(pipePadreHijo2[0], &numeroRecibido, sizeof(int));
        if (esPrimo(numeroRecibido))
        {
            exit(0);
        }
        else
        {
            exit(1);
        }
    }
    else
    {
        int statusHijo1;
        int statusHijo2;
        waitpid(hijo1, &statusHijo1, 0);
        waitpid(hijo2, &statusHijo2, 0);
        if (WIFEXITED(statusHijo1) && WIFEXITED(statusHijo2))
        {
            int exitStatusHijo1 = WEXITSTATUS(statusHijo1);
            int exitStatusHijo2 = WEXITSTATUS(statusHijo2);

            if (exitStatusHijo1 == 0)
            {
                printf("El numero del hijo 1 es primo\n");
            }
            else
            {
                printf("El numero del hijo 1 no es primo\n");
            }

            if (exitStatusHijo2 == 0)
            {
                printf("El numero del hijo 2 es primo\n");
            }
            else
            {
                printf("El numero del hijo 2 no es primo\n");
            }
        }
    }
    close(pipePadreHijo1[0]);
    close(pipePadreHijo2[0]);
    
    return 0;
}
