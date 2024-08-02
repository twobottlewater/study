#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;
    int count = 0;

    while (1) {
        pid = fork();

        if (pid < 0) {
            // fork() 失败
            perror("fork failed");
            break;
        } else if (pid == 0) {
            // 子进程立即退出
            exit(0);
        } else {
            // 父进程计数
            count++;
            printf("已创建子进程数: %d\n", count);
        }
    }

    printf("最大可同时运行的进程数: %d\n", count);

    return 0;
}



/*
已创建子进程数: 3364
已创建子进程数: 3365
已创建子进程数: 3366
已创建子进程数: 3367
已创建子进程数: 3368
已创建子进程数: 3369
已创建子进程数: 3370
已创建子进程数: 3371
已创建子进程数: 3372
已创建子进程数: 3373
已创建子进程数: 3374
已创建子进程数: 3375
已创建子进程数: 3376
已创建子进程数: 3377
已创建子进程数: 3378
已创建子进程数: 3379
已创建子进程数: 3380
已创建子进程数: 3381
fork failed: Resource temporarily unavailable
最大可同时运行的进程数: 3381
*/