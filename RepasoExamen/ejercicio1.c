#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#define LENGTHARRAY 3
int main(int argc, char const *argv[])
{
    int accion[2];
    pid_t procesoClonado;
    if (pipe(accion) == -1)
    {
        perror("No se ha creado el pipe o tubería");
        return 1;
    }
    procesoClonado = fork();

    if (procesoClonado != 0)
    {
        close(accion[0]);
        int numeros[LENGTHARRAY];
        for (int i = 0; i < LENGTHARRAY; i++)
        {

            printf("introduce %d º numero para pasarlo al proceso hijo: ", i);

            scanf("%d", &numeros[i]);
        }
        int escribir = write(accion[1], &numeros, sizeof(numeros));
        if (escribir == -1)
        {
            perror("no se ha podido escribir");
        }
    }
    else
    {
        close(accion[1]);
        int numerosRecibidos[LENGTHARRAY];
        int leer = read(accion[0], numerosRecibidos, sizeof(numerosRecibidos));
        if (leer == -1)
        {
            perror("no se ha podido leer");
        }
        int resultadoOrdenado[LENGTHARRAY];

        if (numerosRecibidos[0] > numerosRecibidos[1] && numerosRecibidos[0] > numerosRecibidos[2])
        {
            resultadoOrdenado[0] = numerosRecibidos[0];
        }
        else if (numerosRecibidos[1] > numerosRecibidos[0] && numerosRecibidos[1] > numerosRecibidos[2])
        {
            resultadoOrdenado[0] = numerosRecibidos[1];
        }
        else
        {
            resultadoOrdenado[0] = numerosRecibidos[2];
        }

        if (numerosRecibidos[0] > numerosRecibidos[1] && numerosRecibidos[0] < numerosRecibidos[2] || numerosRecibidos[0] > numerosRecibidos[2] && numerosRecibidos[0] < numerosRecibidos[1])
        {
            resultadoOrdenado[1] = numerosRecibidos[0];
        }
        else if (numerosRecibidos[1] > numerosRecibidos[0] && numerosRecibidos[1] < numerosRecibidos[2] || numerosRecibidos[1] > numerosRecibidos[2] && numerosRecibidos[1] < numerosRecibidos[0])
        {
            resultadoOrdenado[1] = numerosRecibidos[1];
        }
        else
        {
            resultadoOrdenado[1] = numerosRecibidos[2];
        }
        if (numerosRecibidos[0] < numerosRecibidos[1] && numerosRecibidos[0] < numerosRecibidos[2])
        {
            resultadoOrdenado[2] = numerosRecibidos[0];
        }
        else if (numerosRecibidos[1] < numerosRecibidos[0] && numerosRecibidos[1] < numerosRecibidos[2])
        {
            resultadoOrdenado[2] = numerosRecibidos[1];
        }
        else
        {
            resultadoOrdenado[2] = numerosRecibidos[2];
        }
        printf("Los numeros organizados se han introducido en salida.txt:\n ");
        FILE *salida;
        salida = fopen("e1salida.txt", "w");
        if (salida == NULL)
        {
            perror("No se pudo abrir el archivo");
            return 1;
        }
        for (int i = 0; i < LENGTHARRAY; i++)
        {
            fprintf(salida, "%d\n", resultadoOrdenado[i]);
        }
        fclose(salida);
    }
    return 0;
}
