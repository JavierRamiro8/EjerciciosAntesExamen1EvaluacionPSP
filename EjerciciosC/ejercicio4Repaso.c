#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
int main(int argc, char const *argv[])
{
    int numeroHijos = atoi(argv[1]);
    pid_t hijos[numeroHijos];
    int hijosMatados();
    for (int i = 0; i < numeroHijos; i++)
    {
        if ((hijos[i] = fork()) == 0)
        {
            while (1)
            {
                sleep(1);
            }
        }
    }
    for (int i = 0; i < numeroHijos; i++)
    {
        printf("el hijo %d se ha creado \n", hijos[i]);
        kill(hijos[i], SIGKILL);
        printf("el hijo %d ha muerto\n", hijos[i]);
        waitpid(hijos[i], NULL, 0);
    }

    return 0;
}
