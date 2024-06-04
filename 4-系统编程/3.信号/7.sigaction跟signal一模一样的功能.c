#include "myhead.h"

/*
	sigaction可以实现跟signal一模一样的功能
*/

void fun(int sig)
{
	printf("我捕捉的信号 %d\n",sig);
}
int main(int argc,char **argv)
{
	struct sigaction myaction;
	bzero(&myaction,sizeof(myaction));
	//myaction.sa_handler=fun;  改变INT的响应动作
	myaction.sa_handler=SIG_IGN; //忽略INT信号
	myaction.sa_handler=SIG_DFL; //恢复默认动作
	myaction.sa_flags=0; //开关;

	//捕捉INT信号
	sigaction(SIGINT,&myaction,NULL);
	while(1)
	{
		printf("进程%d在执行!\n",getpid());
		sleep(1);
	}
	return 0;
}