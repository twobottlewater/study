#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


int main() {
    //目的：父进程创建多个子进程
    int n=0;
    int x=0;

    // printf("请输入子进程的数量：");
    // scanf("%d", &n);

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
            while(1);
        }

        printf("进程的个数:%d\n",x);
    }
    
    //子进程不会走到这里，默认下面的代码都是父进程的
    printf("父进程:%d\n",getpid());
    
    while(1);
    //主动回收所有的子进程
    //什么时候不需要主动回收呢？  整个应用程序运行的时间不长，最后整个应用程序结束的时候，就算你这个程序产生了很多个僵尸进程，但是都没有关系，因为系统在你这个应用程序退出的时候，会帮你将这个应用程序所有产生的僵尸进程会回收
    //while(1);

    // for(int i=0;i<n;i++)
    // {
    //     int ret = wait(NULL);
    //     printf("回收子进程[%d]成功\n", ret);
    // }
    

    return 0;
}