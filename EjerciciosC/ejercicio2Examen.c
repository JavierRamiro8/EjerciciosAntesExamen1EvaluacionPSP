#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

static int llamado = 0;

void manejadorDeSenalesUSR1(int signal) {
    llamado++;
    if (llamado == 1) {
        printf("Hola soy el hijo con el pid %d, me han matado\n", getpid());
    } else {
        printf("Hola soy el hijo con el pid %d, me han rematado\n", getpid());
    }
}

void manejadorDeSenalesINT(int signal) {
    if (llamado == 0) {
        printf("soy el hijo %d y no estoy muerto\n", getpid());
    } else {
        printf("soy el hijo %d y estoy muerto\n", getpid());
    }
    exit(0);
}

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <numeroHijos> <numSeñales>\n", argv[0]);
        return 1;
    }

    int numeroHijos = atoi(argv[1]);
    int numSeñales = atoi(argv[2]);
    pid_t arrayHijos[numeroHijos];

    // Creación de procesos hijos.
    for (int i = 0; i < numeroHijos; i++) {
        arrayHijos[i] = fork();
        if (arrayHijos[i] == 0) {
            signal(SIGUSR1, manejadorDeSenalesUSR1);
            signal(SIGINT, manejadorDeSenalesINT);
            while (1) {
                sleep(1); // Espera por la señal.
            }
        }
    }
    srand(time(NULL));
    for (int i = 0; i < numSeñales; i++) {
        int numeroRandomHijo = rand() % numeroHijos;
        kill(arrayHijos[numeroRandomHijo], SIGUSR1);
        sleep(1);
    }

    sleep(1);//Espero a todas las salidas de SIGUSR1 para que no se sobrepongan

    for (int i = 0; i < numeroHijos; i++) {
        kill(arrayHijos[i], SIGINT);
        sleep(1);
    }

    // Esperar a que todos los hijos terminen.
    for (int i = 0; i < numeroHijos; i++) {
        waitpid(arrayHijos[i], NULL, 0);
    }

    return 0;
}