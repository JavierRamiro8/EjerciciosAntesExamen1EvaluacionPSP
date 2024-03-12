#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

#define MAXGENNUM 100
#define HIJO1 "HIJO 1"
#define HIJO2 "HIJO 2"

char primerEncontrado[10] = "";
char segundoEncontrado[10] = "";

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

void manejadorSIGUSR1(int signal)
{
    if (signal == SIGUSR1 && strcmp(primerEncontrado, HIJO2) != 0)
    {
        strcpy(primerEncontrado, HIJO1);
    }
    else
    {
        strcpy(segundoEncontrado, HIJO2);
    }
}

void manejadorSIGUSR2(int signal)
{
    if (signal == SIGUSR2 && strcmp(primerEncontrado, HIJO1) != 0)
    {
        strcpy(primerEncontrado, HIJO1);
    }
    else
    {
        strcpy(segundoEncontrado, HIJO2);
    }
}

int main()
{
    srand(time(NULL));
    pid_t hijo1;
    pid_t hijo2;
    
    signal(SIGUSR1, manejadorSIGUSR1);
    signal(SIGUSR2, manejadorSIGUSR2);

    int numeroRecibido = 3;
    
    int pipeHijo1Padre[2];
    int pipeHijo2Padre[2];
    
    if (pipe(pipeHijo1Padre) != 0 || pipe(pipeHijo2Padre) != 0)
    {
        printf("Error al crear los pipes.\n");
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
            printf("Hijo1 con el numero aleatorio: %d en el indice %d\n", numerosAleatoriosHijo1[i], i);
        }
        
        for (int i = 0; i < numeroRecibidoPadre; i++)
        {
            for (int j = 0; j < numeroRecibidoPadre; j++)
            {
                int resultado = numerosAleatoriosHijo1[i] + numerosAleatoriosHijo1[j];
                if (esPrimo(resultado))
                {
                    kill(getppid(), SIGUSR1);
                }
            }
        }
        
        exit(0); // Importante para que el hijo termine correctamente
    }
    
    else if ((hijo2 = fork()) == 0)
    {
        int numeroRecibidoPadre = 0;
        read(pipeHijo2Padre[0], &numeroRecibidoPadre, sizeof(int));
        
        int numerosAleatoriosHijo2[numeroRecibidoPadre];
        
        for (int i = 0; i < numeroRecibidoPadre; i++)
        {
            numerosAleatoriosHijo2[i] = rand() % MAXGENNUM;
            printf("Hijo2 con el numero aleatorio: %d en el indice %d\n", numerosAleatoriosHijo2[i], i);
        }
        
        for (int i = 0; i < numeroRecibidoPadre; i++)
        {
            for (int j = 0; j < numeroRecibidoPadre; j++)
            {
                int resultado = numerosAleatoriosHijo2[i] + numerosAleatoriosHijo2[j];
                if (esPrimo(resultado))
                {
                    kill(getppid(), SIGUSR2);
                }
            }
        }
        
        exit(0); // Importante para que el hijo termine correctamente
    }
    
    else
    {
        waitpid(hijo1, NULL, 0);
        waitpid(hijo2, NULL, 0);

        if (primerEncontrado[0] == '\0' && segundoEncontrado[0] == '\0')
        {
            printf("Nadie ha encontrado ningún primo de la suma de dos primos.\n");
        }
        
        else if (strcmp(primerEncontrado, HIJO1) == 0 && segundoEncontrado[0] == '\0')
        {
            printf("El primer primo ha sido encontrado por %s.\n", primerEncontrado);
            printf("El segundo no ha encontrado nada.\n");
            
        } 
       else
       {
           printf("El primero que ha encontrado el primer primo de la suma de dos primos es: %s.\n", primerEncontrado);
           printf("El segundo que ha encontrado el primer primo de la suma de dos primos es: %s.\n", segundoEncontrado);
       }
   }

   return 0;
}

