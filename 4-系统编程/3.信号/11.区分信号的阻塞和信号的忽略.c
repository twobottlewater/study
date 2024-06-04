#include "myhead.h"

/*
	信号的忽略：信号发给进程，进程收到之后不响应，直接丢弃该信号
	信号的阻塞/屏蔽：暂时把信号挂起(把信号挡住,信号没有被丢弃，还存在的),如果你解除阻塞，依然可以响应
*/

int main()
{
	int i;
	printf("进程ID %d\n",getpid());
	//第一步：定义集合变量，存放你要阻塞的所有信号
	// sigset_t myset;
	// sigemptyset(&myset); //清空集合
	//添加你想阻塞的信号--》SIGINT和SIGQUIT	屏蔽
	// sigaddset(&myset,SIGINT);
	// sigaddset(&myset,SIGQUIT);
	
	//第二步：设置阻塞
	// sigprocmask(SIG_BLOCK,&myset,NULL);
	
	signal(SIGINT,SIG_IGN);
	signal(SIGQUIT,SIG_IGN);

	for(i=0; i<20; i++)
	{
		printf("这20秒的时间，你给我发送INT、QUIT信号是没有用的!\n");
		sleep(1);
	}
	
	//偷偷摸摸解除阻塞
	//sigprocmask(SIG_UNBLOCK,&myset,NULL);
	
	signal(SIGINT,SIG_DFL);
	signal(SIGQUIT,SIG_DFL);
	
	for(i=0; i<20; i++)
	{
		printf("这20秒的时间，刚才的信号已经解除阻塞了!\n");
		sleep(1);
	}
	
	//阻塞进程等待信号的到来
	pause();
	
	return 0;
}