#include "myhead.h"

/*
	alarm函数的使用
*/

void fun(int sig)
{
	printf("我收到了信号 %d\n",sig);
}
int main()
{
	signal(SIGALRM,fun);
	//调用alarm函数
	alarm(5); //间隔5秒钟，alarm会自动给当前进程发送SIGALRM
	printf("主函数接着往后执行!\n");
	pause();
	return 0;
}