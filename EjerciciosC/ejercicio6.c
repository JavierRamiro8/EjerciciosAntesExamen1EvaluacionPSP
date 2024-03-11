#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>

int main(int argc, char const *argv[])
{
    int numero1 = atoi(argv[1]);
    char simboloOperacion = argv[2][0];
    int numero2 = atoi(argv[3]);
    printf("expresion por parametro recogida por el padre: %d %c %d\n", numero1, simboloOperacion, numero2);
    int pipeHijo1[2];
    if (pipe(pipeHijo1) != 0)
    {
        printf("el pipe ha fallado");
        exit(1);
    }
    write(pipeHijo1[1], &numero1, sizeof(int));
    write(pipeHijo1[1], &simboloOperacion, sizeof(int));
    write(pipeHijo1[1], &numero2, sizeof(int));
    pid_t hijo1;

    if ((hijo1 = fork()) == 0)
    {
        int numeroRecibido1;
        int numeroRecibido2;
        char simboloOperacionRecibido;
        read(pipeHijo1[0], &numeroRecibido1, sizeof(int));
        read(pipeHijo1[0], &simboloOperacionRecibido, sizeof(int));
        read(pipeHijo1[0], &numeroRecibido2, sizeof(int));
        printf("EL envio del padre al hijo: %d %c %d\n", numeroRecibido1, simboloOperacionRecibido, numeroRecibido2);
        int resultado;
        if (simboloOperacionRecibido == '+')
        {
            resultado = numeroRecibido1 + numeroRecibido2;
        }
        else
        {
            resultado = numeroRecibido1 - numeroRecibido2;
        }
        write(pipeHijo1[1],&resultado,sizeof(int));
        exit(0);
    }
    waitpid(hijo1,NULL,0);
    int resultadoRecibido;
    read(pipeHijo1[0],&resultadoRecibido,sizeof(int));
    printf(" el resultado es: %d\n",resultadoRecibido);
    return 0;
}
