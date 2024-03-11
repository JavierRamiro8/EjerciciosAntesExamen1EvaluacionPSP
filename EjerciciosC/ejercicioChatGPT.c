/*
Objetivo del programa: Crear un programa en C que inicie dos procesos hijos. Estos procesos se comunicarán entre sí usando pipes y responderán a señales específicas enviadas por el proceso padre.

Requisitos funcionales:
Inicio del Programa:

El programa principal (main) debe iniciar y crear un pipe.
Luego, debe crear dos procesos hijos (utilizando fork()).
Estos procesos hijos se comunicarán entre sí a través del pipe creado por el padre.
Comunicación entre Procesos:

Uno de los procesos hijos será el emisor y el otro el receptor.
El proceso emisor enviará mensajes al receptor a través del pipe.
El proceso receptor leerá estos mensajes y los imprimirá en la consola.
Manejo de Señales:

El proceso padre debe manejar las señales SIGUSR1, SIGUSR2, y SIGINT.
Al recibir SIGUSR1, el proceso padre le indicará al proceso emisor que envíe un mensaje específico al receptor.
Al recibir SIGUSR2, el proceso padre le indicará al proceso emisor que envíe un mensaje diferente.
Al recibir SIGINT (Ctrl+C), el programa deberá cerrar los pipes, terminar los procesos hijos de forma segura y luego terminar él mismo.
Terminación del Programa:

Implementar el envío de la señal SIGKILL desde el padre para terminar uno de los procesos hijos como parte de la limpieza final del programa.*/
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#define MAXGENNUM 3
int compararNumeros(const void *a, const void *b)
{
    return (*(int *)b - *(int *)a);
}
void manejadorDeSenales(int signal)
{
    if (signal == SIGUSR1)
    {
        printf("Hola soy el hijo con el pid %d, me han rematado\n", getpid());
    }
    else if (signal == SIGUSR2)
    {
        printf("Hola soy el hijo con el pid %d, me han matado\n", getpid());
    }
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    int compararNumeros();
    void manejadorDeSenales(int signal);
    signal(SIGUSR2, manejadorDeSenales);
    pid_t hijo1;
    pid_t hijo2;
    int pipeHijo1[2];
    int pipeHijo2[2];
    if (pipe(pipeHijo1) != 0)
    {
        printf("El pipe del hijo1 ha fallado");
        return 1;
    }
    if (pipe(pipeHijo2) != 0)
    {
        printf("El pipe del hijo1 ha fallado");
        return 1;
    }
    int numerosRandom[3];
    for (int i = 0; i < MAXGENNUM; i++)
    {
        numerosRandom[i] = rand() % 100;
        printf("%d\n", numerosRandom[i]);
    }
    write(pipeHijo1[1], numerosRandom, sizeof(numerosRandom));
    if ((hijo1 = fork()) == 0)
    {
        close(pipeHijo1[1]);
        int numerosRandomRecibido[MAXGENNUM];
        read(pipeHijo1[0], numerosRandomRecibido, sizeof(numerosRandomRecibido));
        qsort(numerosRandomRecibido, MAXGENNUM, sizeof(int), compararNumeros);
        printf("Los numeros Ordenados son: \n");
        for (int i = 0; i < MAXGENNUM; i++)
        {
            printf("%d\n", numerosRandomRecibido[i]);
        }
        signal(SIGUSR1, manejadorDeSenales);
        signal(SIGUSR2, manejadorDeSenales);
        pause();
        pause();
    }
    else if ((hijo2 = fork()) == 0)
    {
        printf("soy el hijo 2, veremos a ver cual es mi pid\n");
        signal(SIGUSR1, manejadorDeSenales);
        signal(SIGUSR2, manejadorDeSenales);
        pause();
        pause();
    }
    else
    {
        sleep(1);
        kill(hijo1, SIGUSR1);
        sleep(1);
        kill(hijo1, SIGUSR2);
        sleep(1);
        kill(hijo2, SIGUSR1);
        sleep(1);
        kill(hijo2, SIGUSR2);
        wait(NULL);
        wait(NULL);
    }
    return 0;
}
