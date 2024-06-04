#include "myhead.h"

/*
	sigaction使用另外一个响应函数
*/

void fun(int sig,siginfo_t *info,void *arg)
{
	printf("我捕捉的信号 %d 携带的额外数据是: %d\n",sig,info->si_int);
}
int main(int argc,char **argv)
{
	struct sigaction myaction;
	bzero(&myaction,sizeof(myaction));
	myaction.sa_sigaction=fun;  //改变INT的响应动作
	myaction.sa_flags=SA_SIGINFO; //开关;

	//捕捉INT信号
	sigaction(SIGINT,&myaction,NULL);
	while(1)
	{
		printf("进程%d在执行!\n",getpid());
		sleep(1);
	}
	

	return 0;
}