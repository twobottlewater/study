#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void create_process_chain(int n) {
    pid_t pid;

    if (n <= 0) {
        return;
    }

    pid = fork();

    if (pid < 0) {
        // fork() 失败
        perror("fork failed");
        exit(1);
    } else if (pid > 0) {
        // 父进程
        printf("父进程 PID: %d\n", getpid());
        exit(0); // 父进程退出
    } else {
        // 子进程
        sleep(1); // 确保子进程的PID比父进程大
        create_process_chain(n - 1);
        printf("子进程 PID: %d\n", getpid());
    }
}

int main() {
    int n = 5; // 设置链的长度

    create_process_chain(n);

    return 0;
}