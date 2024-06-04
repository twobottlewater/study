#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


int main() {
    //目的：父进程创建多个子进程
    int n=0;
    int x=0;

    printf("请输入子进程的数量：");
    scanf("%d", &n);

    while (1)
    {
        x++;

        pid_t pid = fork();
        if(pid == -1)
        {
            printf("创建进程失败\n");
            break;
        }
        else if(pid == 0)
        {
            printf("子进程[%d]:%d创建成功 ppid:%d\n", x,getpid(),getppid());
            
        }
        else if(pid > 0)
        {
            printf("父进程[%d]\n", getpid());
            int ret = wait(NULL);
            printf("回收子进程[%d]成功\n", ret);

            exit(0);
        }
        if(x == n)
        {
            break;
        }
    }
  

    return 0;
}