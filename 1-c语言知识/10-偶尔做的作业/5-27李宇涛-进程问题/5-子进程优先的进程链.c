#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void create_process_chain(int n) {
    if (n <= 0) {
        return;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // 子进程
        printf("子进程 PID: %d, 父进程 PID: %d\n", getpid(), getppid());
        create_process_chain(n - 1);
        exit(0); // 子进程退出
    } else {
        // 父进程
        wait(NULL); // 等待子进程结束
        printf("父进程 PID: %d\n", getpid());
        exit(0); // 父进程退出
    }
}

int main() {
    int n = 5; // 设置链的长度

    create_process_chain(n);

    return 0;
}
