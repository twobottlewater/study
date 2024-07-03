#include "myhead.h"

/*
	  1.用3) SIGQUIT	 4) SIGILL	 5) SIGTRAP这三个信号分别代表红绿黄交通信号灯
       要求：当进程收到红灯信号SIGQUIT，程序打印"红灯停"
             当进程收到绿灯信号SIGILL， 程序打印"绿灯行"
             当进程收到绿灯信号SIGTRAP， 程序打印"黄灯主要观察注意"
*/
void fun(int sig)
{
	if(sig==SIGQUIT)
		printf("红灯停!\n");
	if(sig==SIGILL)
		printf("绿灯行!\n");
	if(sig==SIGTRAP)
		printf("黄灯主要观察注意!\n");
}
int main()
{
	signal(SIGQUIT,fun);
	signal(SIGILL,fun);
	signal(SIGTRAP,fun);
	
	pause();
	return 0;
	
}