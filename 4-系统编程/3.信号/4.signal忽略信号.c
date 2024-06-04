#include "myhead.h"

/*
	signal的三种用法
	 第一种：改变信号的响应
			 signal(信号,函数指针)
	 第二种：忽略信号--》当外界给进程发送这个信号的时候，进程选择左耳进右耳出
			 signal(信号,SIG_IGN)  
	 第三种：默认动作
			 signal(信号,SIG_DFL)  
*/
void fun(int sig)
{
	printf("收到的信号%d\n",sig);
}


int main(int argc,char **argv)
{
	int i;
	//最开始我选择忽略INT信号
	//默认情况：SIGINT收到之后会导致当前进程终止
	//signal(SIGINT,SIG_IGN);  
	signal(SIGQUIT,fun);
	for(i=0; i<20; i++)
	{
		printf("忽略SIGQUIT，当前进程正在运行%d\n",getpid());
		sleep(1);
	}
	
	//我改变主意了，我要恢复INT信号的默认动作
	signal(SIGQUIT,SIG_DFL);
	
	for(i=0; i<20; i++)
	{
		printf("恢复默认动作之后，当前进程正在运行%d\n",getpid());
		sleep(1);
	}
	return 0;
}