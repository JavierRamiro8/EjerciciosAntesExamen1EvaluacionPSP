#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#define MAXRANDGENNUM 100
#define MAXROUND 5
/*el funcionamiento de este ejercicio es un adivinar el numero entre el padre
y el hijo usando señales te dira si es mayor, menor o lo has acertado*/
void manejadorSenialesSIGUSR1(int signal)
{
    printf("Intento 12345");
}
void manejadorSenialesSIGUSR2(int signal)
{
    exit(0);
}
int main(int argc, char const *argv[])
{
    pid_t hijo;
    int pipeHijo[2];
    if (pipe(pipeHijo) != 0)
    {
        printf("el pipe ha fallado\n");
        return 1;
    }
    if ((hijo = fork()) == 0)
    {
        srand(time(NULL));
        int numeroAleatorio = rand() % MAXRANDGENNUM;
        write(pipeHijo[1], &numeroAleatorio, sizeof(int));
        signal(SIGUSR1, manejadorSenialesSIGUSR1);
        signal(SIGUSR1, manejadorSenialesSIGUSR2);
        for (int i = 0; i < MAXROUND; i++)
        {
            pause();
        }
        exit(0);
    }
    else
    {
        int numeroRandomRecibido;
        read(pipeHijo[0], &numeroRandomRecibido, sizeof(int));
        int numero=0;
        printf("ponme un numero y haber si lo aciertas, tienes %d intentos\n", MAXROUND);
        scanf("%d", &numero);
        for (int i = 1; i < MAXROUND; i++)
        {
            if (numero > numeroRandomRecibido)
            {
                printf("Te has pasado, mas bajo el numero\n");
                kill(hijo, SIGUSR1);
                printf("elige otro: ");
                scanf("%d", &numero);
            }
            else if (numero < numeroRandomRecibido)
            {
                printf("Te has quedado corto, mas alto el numero\n");
                kill(hijo, SIGUSR1);
                printf("elige otro: ");
                scanf("%d", &numero);
            }
            else
            {
                kill(hijo, SIGUSR2);
                printf("la has clavado");
                break;
            }
            if(i==MAXROUND-1){
                printf("Al final no lo has acertado, el numero era %d\n",numeroRandomRecibido);
            }
        }
    }
    waitpid(hijo, NULL, 0);

    return 0;
}
