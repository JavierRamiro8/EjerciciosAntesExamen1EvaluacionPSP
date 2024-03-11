#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    char* comando="ipconfig";
    char* argumentos[]={"ipconfig","/all",NULL};
    execvp(comando,argumentos);
    return 0;
}