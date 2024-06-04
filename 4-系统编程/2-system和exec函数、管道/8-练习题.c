#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>



int main(int argc,char *argv[]) 
{
    pid_t pid = fork();
    if(pid == 0)
    {
        // 子进程
        printf("子进程:%d\n",getpid());
        int ret = execl("./mtime","mtime","li4",NULL);
        if(ret == -1)
        {
            perror("execl");
            exit(1);
        }
    }
    int i=0;

    while(1){
        sleep(1);
        printf("父进程[%d]:%d\n",getpid(),i++);
    }

    printf("阻塞等待子进程的结束\n");
    wait(NULL);

    return 0;
}