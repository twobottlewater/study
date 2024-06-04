#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>



int main()
{   

    pid_t pid = fork(); // 创建一个子进程
    int n=666;
    if (pid < 0) {
        // 错误处理：fork失败
        fprintf(stderr, "fork failed");
        exit(0);
    } else if (pid == 0) {
        // 子进程
        n=777;
        printf("子进程的n的值：%d\n",n);
        printf("Child process: My parent is %d\n", getppid());
        sleep(10); // 睡眠5秒，等待父进程退出
        printf("Child process: Now my parent is %d\n", getppid()); // 再次打印父进程ID，此时应该是1（init进程）
    } else {
        // 父进程
        printf("Parent process: My child is %d\n", pid);
        sleep(5); // 父进程睡眠1秒后退出
        printf("Parent process exiting\n");
        printf("父进程的n的值：%d\n",n);
        exit(0);
    }

    return 0;


}