#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#define MAXRANDNUM 3
int compararNumeros(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}
int main(int argc, char const *argv[])
{
    srand(time(NULL));
    int puenteHijo1[2];
    if (pipe(puenteHijo1)!=0)
    {
        printf("El pipe ha fallado");
        return 1;
    }
    int numerosAleatorios[MAXRANDNUM];
    for (int i = 0; i < MAXRANDNUM; i++)
    {
        numerosAleatorios[i]=rand()%10;
        printf("soy el padre y este es mi numero %d\n",numerosAleatorios[i]);
    }
    write(puenteHijo1[1],numerosAleatorios,sizeof(numerosAleatorios));
    pid_t hijo1;
    hijo1=fork();
    if(hijo1==0){
        close(puenteHijo1[1]);
        int numerosAleatoriosRecibidos[MAXRANDNUM];
        read(puenteHijo1[0],numerosAleatoriosRecibidos,sizeof(numerosAleatoriosRecibidos));
        qsort(numerosAleatoriosRecibidos,MAXRANDNUM,sizeof(int),compararNumeros);
        FILE *archivo;
        archivo=fopen("salida.txt","w+");
        for (int i = 0; i < MAXRANDNUM; i++)
        {
            fprintf(archivo,"%d\n",numerosAleatoriosRecibidos[i]);
        }
        fclose(archivo);
        return 0;
    }
    wait(NULL);
    printf("el padre a finalizado");
    return 0;
}
