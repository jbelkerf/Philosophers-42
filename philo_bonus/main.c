// #include "philo.h"

// void routine1(char *name, sem_t *sm)
// {
//     printf("%s is here\n", name);
//     int i = 0;
//     while (i < 100)
//     {
//         //printf("i = %d\n", i);
//         sem_wait(sm);
//         printf("%s in\n", name);
//         sleep(1);
//         sem_post(sm);
//         sleep(1);
//         i++;
//     }
//     sem_close(sm);
// }

// int main()
// {
//          // Parent closes
//     sem_unlink("/sem");

//     sem_t   *sm = sem_open("/sem", O_CREAT, 0766, 1);

//     int pid = fork();
//     if (pid == 0)
//     {
//         routine1("lwl", sm);
//         return 1;
//     }
//     pid = fork();
//     if (pid == 0)
//     {
//         routine1("tani", sm);
//         return 1;
//     }
//     while (wait(NULL) > 0)
//     ;
//     sem_close(sm);        // Parent closes
//     sem_unlink("/sem"); 
//     //wait(NULL);
// }

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int pid = fork();
    if (pid == 0)
    {
        int i = 0;
        while (i < 100)
        {
            printf("lwl %d\n", i);
            sleep(1);
            i++;
        }
        exit(1);
    }
    int pid2 = fork();
    if (pid2 == 0)
    {
        int i = 0;
        while (i < 100)
        {
            printf("tani %d\n", i);
            sleep(1);
            i++;
        }
        exit(1);
    }
    waitpid(pid, 0,0);
    waitpid(pid2, 0,0);
}