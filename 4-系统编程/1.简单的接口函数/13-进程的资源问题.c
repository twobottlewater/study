#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int val = 0;

int main() 
{
    pid_t pid = fork();
    if (pid == 0)
    {
        val = 100;
        printf("子进程 val = %d\n",val); //100
        sleep(10);
        //子进程
        exit(0);
    }
    else if(pid > 0 )
    {
        //父进程
        sleep(5);
        printf("父进程 val = %d\n",val); //
    }

    return 0;
}