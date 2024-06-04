#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    printf("游戏........\n");

    //在进程中加载新的脚本或者程序，覆盖原来进程的所有代码，重新运行
    //游戏运行过程中，需要启动脚本 --刷副本
    printf("脚本启动....\n");
    execl("./lei","lei","zhang3",NULL);

    printf("脚本结束\n");

    printf("游戏继续........\n");
    sleep(1);

    printf("游戏结束........\n");
    return 0;
}