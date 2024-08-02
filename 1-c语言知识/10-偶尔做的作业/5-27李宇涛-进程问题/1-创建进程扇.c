#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_CHILDREN 5  // 定义要创建的子进程数量

int main() {
    pid_t pid;
    int i;

    for (i = 0; i < NUM_CHILDREN; i++) {
        pid = fork();

        if (pid < 0) {
            perror("fork failed");
            exit(1);
        } else if (pid == 0) {
            // 子进程
            printf("子进程 PID: %d, 父进程 PID: %d\n", getpid(), getppid());
            exit(0);  // 子进程退出
        }
    }

    // 父进程等待所有子进程终止
    for (i = 0; i < NUM_CHILDREN; i++) {
        wait(NULL);
    }

    // 父进程打印其 PID
    printf("父进程 PID: %d\n", getpid());

    return 0;
}
