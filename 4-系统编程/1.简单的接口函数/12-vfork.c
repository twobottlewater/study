#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int val = 0;

int main() 
{
    pid_t pid = vfork();
    if (pid == 0) 
    {
        val = 100;
        printf("子进程 val = %d\n",val); //100

        int n=10;
        while (n--)
        {
            /* code */
            sleep(1);
            printf("子进程 n = %d\n",n); //10 9 8 7 6 5 4 3 2 1 0
        }
        
        exit(0);//子进程一定要调用exit退出
    }
    else if(pid > 0 )
    {
        //父进程

        printf("父进程 val = %d\n",val); //
    }

    return 0;
}