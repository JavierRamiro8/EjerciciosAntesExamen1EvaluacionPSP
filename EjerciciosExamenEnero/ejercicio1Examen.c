#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int esPrimo(int num) {
    if (num < 2) return 0;
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int generarNumero(int longitud) {
    int rangoInicial = 1;
    int rangoFinal = 1;

    for (int i = 1; i < longitud; ++i) {
        rangoInicial *= 10;
        rangoFinal *= 10;
    }
    rangoFinal = rangoFinal * 10 - 1;

    return rand() % (rangoFinal - rangoInicial + 1) + rangoInicial;
}

void imprimirResultado(const char *hijo, int numero, int esPrimo) {
    int estaVivo;
    printf("%s: %d ", hijo, numero);
    if (esPrimo) {
        printf("primo, ");
        estaVivo=0;
    } else {
        printf("no primo, ");
        estaVivo=1;
    }

    if (estaVivo) {
        printf("vivo\n");
    } else {
        printf("muerto\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s longitud_numeros cantidad_numeros\n", argv[0]);
        return 1;
    }

    int longitud = atoi(argv[1]);
    int cantidad = atoi(argv[2]);

    srand(time(NULL)); // Inicializar la semilla con el tiempo actual

    int pipe_hijo1[2];
    int pipe_hijo2[2];

    if (pipe(pipe_hijo1) == -1 || pipe(pipe_hijo2) == -1) {
        perror("Error al crear las tuberías");
        return 1;
    }

    pid_t hijo1, hijo2;

    if ((hijo1 = fork()) == 0) {
        close(pipe_hijo1[1]);

        int numero;
        while (read(pipe_hijo1[0], &numero, sizeof(int)) > 0) {
            if (numero == -1) {
                // Fin de los números
                break;
            }
            imprimirResultado("Hijo 1", numero, esPrimo(numero));
        }

        close(pipe_hijo1[0]);
        exit(0);
    }

    if ((hijo2 = fork()) == 0) {
        close(pipe_hijo2[1]);

        int numero;
        while (read(pipe_hijo2[0], &numero, sizeof(int)) > 0) {
            if (numero == -1) {
                // Fin de los números
                break;
            }
            imprimirResultado("Hijo 2", numero, esPrimo(numero));
        }

        close(pipe_hijo2[0]);
        exit(0);
    }

    close(pipe_hijo1[0]);
    close(pipe_hijo2[0]);

    for (int i = 0; i < cantidad; ++i) {
        int numero = generarNumero(longitud);
        write(pipe_hijo1[1], &numero, sizeof(int));
        write(pipe_hijo2[1], &numero, sizeof(int));
    }

    // Indicar a los hijos que no hay más números
    int fin = -1;
    write(pipe_hijo1[1], &fin, sizeof(int));
    write(pipe_hijo2[1], &fin, sizeof(int));

    // Cerrar las tuberías después de escribir los números y señal de fin
    close(pipe_hijo1[1]);
    close(pipe_hijo2[1]);

    // Esperar a que ambos hijos terminen
    waitpid(hijo1, NULL, 0);
    waitpid(hijo2, NULL, 0);

    printf("Fin\n");

    return 0;
}


