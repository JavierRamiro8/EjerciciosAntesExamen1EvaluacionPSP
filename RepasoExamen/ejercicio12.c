#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>

#define CERO 0
#define UNO 1
#define DOS 2
#define TRES 3
#define CINCO 5
#define SEIS 6

int esPrimo(int num) {
    if (num <= UNO) {
        return CERO;
    }
    if (num <= TRES) {
        return UNO;
    }
    if (num % DOS == CERO || num % TRES == CERO) {
        return CERO;
    }

    for (int i = CINCO; i * i <= num; i += SEIS) {
        if (num % i == CERO || num % (i + DOS) == CERO) {
            return CERO;
        }
    }
    return UNO;
}

int longitudNumero(int num, int longitud) {
    int count = CERO;
    while (num != CERO) {
        num /= 10;
        count++;
    }
    return count == longitud;
}

int main(int argc, char const *argv[]) {
    printf("Introduce la longitud n para encontrar números primos: ");
    int longitud;
    scanf("%d", &longitud);

    printf("Introduce el número de procesos a utilizar: ");
    int numProcesos;
    scanf("%d", &numProcesos);

    int numerosPorProceso = 100;

    for (int i = 0; i < numProcesos; i++) {
        pid_t proceso = fork();

        if (proceso == 0) { // Proceso hijo
            int inicio = i * numerosPorProceso + 1;
            int fin = (i + 1) * numerosPorProceso;

            for (int j = inicio; j <= fin; j++) {
                if (esPrimo(j) && longitudNumero(j, longitud)) {
                    printf("%d es primo\n", j);
                }
            }
            exit(0);
        }
    }

    // Esperar a que todos los procesos terminen
    for (int i = 0; i < numProcesos; i++) {
        wait(NULL);
    }
    return 0;
}

