#include "myhead.h"

/*
	演示signal的使用
	  总结：linux中的信号有如下几种功能
	        功能1：进程收到信号之后，可以采用linux规定好的默认动作响应(绝大部分信号都会导致程序直接退出)
			功能2：程序员也可以通过signal函数改变信号的响应动作       
*/
void fun(int sig)
{
	printf("我收到INT信号了，信号的数字编号是: %d  我现在播放音乐，跳个舞！\n",sig);
}
int main(int argc,char **argv)
{
	//改变2号信号SIGINT的响应动作
	//默认情况：SIGINT收到之后会导致当前进程终止
	//现在：彭老师想要当前收到SIGINT信号之后，播放音乐，跳个舞
	signal(SIGINT,fun);  //STOP和KILL能不能改变默认响应动作 
	
	while(1)
	{
		printf("当前进程正在运行%d\n",getpid());
		sleep(1);
	}
	return 0;
}