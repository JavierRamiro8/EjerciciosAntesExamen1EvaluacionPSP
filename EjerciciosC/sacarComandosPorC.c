#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void ejecutarComandoConFlag(char *comandoIntroducido, char *flagIntroducida)
{
    char *argumentosConFlag[] = {comandoIntroducido, flagIntroducida, NULL};
    execvp(comandoIntroducido, argumentosConFlag);
    perror("execvp");
}

void ejecutarComandoSinFlag(char *comandoIntroducido)
{
    char *argumentosSinFlag[] = {comandoIntroducido, NULL};
    execvp(comandoIntroducido, argumentosSinFlag);
    perror("execvp");
}

int main(int argc, char const *argv[])
{
    char *comandoPrincipal = malloc(100);
    printf("Introduce el comando principal: ");
    scanf("%s", comandoPrincipal);
    printf("Quieres introducir alguna flag (0/1): ");
    int respuesta = 0;
    scanf("%d", &respuesta);

    if (respuesta == 0)
    {
        ejecutarComandoSinFlag(comandoPrincipal);
    }
    else
    {
        char flagPrincipal[100];
        printf("Pon la flag: ");
        scanf("%s", flagPrincipal);
        ejecutarComandoConFlag(comandoPrincipal, flagPrincipal);
    }

    return 0;
}

