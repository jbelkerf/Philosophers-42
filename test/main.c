#include <pthread.h>
#include <stdio.h>
#include <unistd.h> // for sleep
#include <sys/wait.h>


// This function will be executed by the detached thread
int main()
{
    int n = 10;
    int *p  = &n;
    printf("%p\n", p);
    int pid = fork();
    if (pid == 0)
    {
    printf("%p\n", p);

        (p++);
       
    }else{
        usleep(4000000);
        printf("n = %d", n);
    }
}
