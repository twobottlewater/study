#include "myhead.h"

/*
	信号的阻塞/屏蔽
*/

int main()
{
	printf("进程ID %d\n",getpid());
	//第一步：定义集合变量，存放你要阻塞的所有信号
	sigset_t myset;
	sigemptyset(&myset); //清空集合
	//添加你想阻塞的信号--》SIGINT和SIGQUIT	屏蔽
	sigaddset(&myset,SIGINT);
	sigaddset(&myset,SIGQUIT);
	
	//第二步：设置阻塞
	/*
		SIG_BLOCK   //设置信号阻塞，把set和oset两个集合中的所有信号都阻塞
        SIG_SETMASK //设置信号阻塞，只阻塞set这个集合中的所有信号
	*/
	sigset_t oldset;
	sigprocmask(SIG_BLOCK,&myset,&oldset);
	//sigprocmask(SIG_SETMASK,&myset,&oldset);
	
	//阻塞进程等待信号的到来
	pause();
	
	return 0;
}