#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#if 0
int execl(const char *pathname, const char *arg, ...);
函数作用：在进程中加载新的脚本或者程序，覆盖原来进程的所有代码，重新运行
参数：
    pathname：要执行的程序的路径名
    arg:执行该程序时，需要携带的参数
        必须是以自身名字开头 ，以NULL作为结束
返回值：
    失败返回 -1
比如说，现在执行 lei脚本程序 
    execl("./lei","lei","zhang3",NULL);

#endif 

int main() 
{
    printf("部落冲突游戏................\n");
    int n;

    printf("[1]注册  [2]登录:");
    scanf("%d", &n);

    switch (n)
    {
        case 1:
            /* code */
            break;
        case 2:
            /* code */
            break;
        default:
            break;
    }

    //主界面
    while(1)
    {
        printf("[1]刷副本  [2]打野  [3]退出游戏");
        scanf("%d", &n);

        switch (n)
        {
            case 1:
                /* code 启动副本程序*/
                {
                    //创建一个子进程，由子进程去启动副本程序
                    pid_t pid = vfork();
                    if(pid == 0)
                    {
                        //子进程
                        int ret = execl("./lei","lei","zhang3",NULL);
                        printf("ret:%d\n",ret);
                        printf("1111111111\n");
                    }
                } 
                break;
            case 2:
                /* code */
                break;
            case 3:
                exit(0);
                break;
            default:
                break;
        }


    }


    return 0;
}