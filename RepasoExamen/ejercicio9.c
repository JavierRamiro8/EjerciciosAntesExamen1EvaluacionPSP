#include <stdio.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
    char *argumentos = "ipconfig";
    char *comando[] = {"ipconfig", NULL};
    execvp(argumentos, comando);
    return 0;
}
