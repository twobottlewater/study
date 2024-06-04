#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#if 0
#include <sys/wait.h>

       pid_t wait(int *stat_loc);
       pid_t waitpid(pid_t pid, int *stat_loc, int options);

函数作用：阻塞等待 主动回收子进程的资源,也就是让子进程从 僵尸态 变成 死亡态

参数：
        stat_loc 获取子进程退出的时候 ，子进程的退出状态 ，不关心，传NULL
#endif  


int main()
{   

    pid_t pid = fork(); // 创建一个子进程

    if (pid < 0) {
        // 错误处理：fork失败
        fprintf(stderr, "fork failed");
        exit(0);
    } else if (pid == 0) {
        // 子进程
        printf("Child process: My parent is %d\n", getppid());
        sleep(10); // 睡眠5秒，等待父进程退出
        printf("Child process: Now my parent is %d\n", getppid()); // 再次打印父进程ID，此时应该是1（init进程）
    } else {
        // 父进程
        printf("Parent process: My child is %d\n", pid);
        sleep(5); // 父进程睡眠1秒后退出
        printf("Parent process exiting\n");
        exit(0);
    }

    return 0;


}