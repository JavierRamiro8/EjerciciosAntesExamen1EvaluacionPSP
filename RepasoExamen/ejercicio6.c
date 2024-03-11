#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    if (argc != 4)
    {
        printf("Valores Incompletos\n");
        return 1;
    }
    int numero1 = atoi(argv[1]);
    char simbolo = argv[2][0];
    int numero2 = atoi(argv[3]);
    int accion[2];
    int resultado = 0;

    pid_t hijo = fork();
    pipe(accion);

    if (hijo == 0)
    {
        close(accion[0]); // Cerramos lectura en el proceso hijo
        write(accion[1], &numero1, sizeof(numero1));
        write(accion[1], &numero2, sizeof(numero2));
        write(accion[1], &simbolo, sizeof(simbolo));
        close(accion[1]); // Cerramos escritura en el proceso hijo
        exit(0);
    }
    else
    {
        close(accion[1]); // Cerramos escritura en el proceso padre
        read(accion[0], &numero1, sizeof(numero1));
        read(accion[0], &numero2, sizeof(numero2));
        read(accion[0], &simbolo, sizeof(simbolo));
        char sumar = '+';
        if (simbolo == '+')
        {
            resultado = numero1 + numero2;
        }
        else
        {
            resultado = numero1 - numero2;
        }
        close(accion[0]);
        wait(NULL);
        printf("%d %c %d es igual a %d\n", numero1, simbolo, numero2, resultado);
        exit(0);
    }
    return 0;
}
