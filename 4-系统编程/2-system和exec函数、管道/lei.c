#include <stdio.h>


//char argv[10][256]
int main(int argc,char**argv)
{
    //argc表示的是传递进来的参数的总个数
    //argv表示的是传递进来的所有参数的数组
    //argv[0]表示的是当前执行的程序的路径
    //argv[1]表示的是第一个参数
    //argv[2]表示的是第二个参数
    //argv[3]表示的是第三个参数
    // printf("argc:%d\n",argc);
    // for(int i=0;i<argc;i++)
    // {
    //     printf("argv[%d]:%s\n",i,argv[i]);
    // }
    if(argc>1)
    {
        printf("当前启动脚本的用户是:%s\n",argv[1]);
    }
    

    printf("正在进入雷峰塔副本........\n");
    sleep(1);
    printf("正在加载副本数据........\n");
    sleep(1);

    printf("正在执行副本任务........\n");
    sleep(1);
    printf("副本任务执行完毕........\n");
    sleep(1);
    printf("副本任务结算........\n");
    sleep(1);
    printf("副本任务结算完毕........\n");
    sleep(1);
    printf("正在退出副本........\n");
    sleep(1);
  

    return 0;
}