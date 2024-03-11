#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#define MAX_CHARACTERS 26
#define CERO 0

// Función para generar combinaciones de caracteres únicas
void generateCombinations(FILE *file, int length)
{
    char combination[length + 1];
    memset(combination, 'a', length);
    combination[length] = '\0';

    char end[length + 1];
    memset(end, 'z', length);
    end[length] = '\0';

    do
    {
        fprintf(file, "%s\n", combination);

        // Generar la siguiente combinación lexicográfica
        int i = length - 1;
        while (i >= CERO && combination[i] == 'z')
        {
            i--;
        }
        if (i >= CERO)
        {
            combination[i]++;
            for (int j = i + 1; j < length; j++)
            {
                combination[j] = 'a';
            }
        }
    } while (strcmp(combination, end) != CERO);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Uso: %s <número de hijos>\n", argv[CERO]);
        return 1;
    }

    int numHijos = atoi(argv[1]);

    if (numHijos <= CERO)
    {
        printf("El número de hijos debe ser un entero positivo.\n");
        return 1;
    }

    // Bucle para crear hijos
    for (int i = 1; i <= numHijos; i++)
    {
        pid_t child = fork();

        if (child < CERO)
        {
            perror("Error al crear el proceso hijo");
            return 1;
        }
        else if (child == CERO)
        {
            // Proceso hijo

            // Crear el nombre del archivo
            char filename[15];
            sprintf(filename, "datos%d.txt", i);

            // Abrir el archivo para escritura
            FILE *file = fopen(filename, "w");

            if (file == NULL)
            {
                perror("Error al abrir el archivo para escritura");
                return 1;
            }

            // Generar combinaciones de caracteres
            generateCombinations(file, i);

            fclose(file);
            exit(CERO);
        }
    }

    // Esperar a que todos los hijos terminen
    for (int i = CERO; i < numHijos; i++)
    {
        wait(NULL);
    }

    return 0;
}
