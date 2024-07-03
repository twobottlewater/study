#include "myhead.h"

/*
	编写一段程序，创建两个子进程，用signal让父进程捕捉SIGINT,
       当捕获到SIGINT,父进程用kill向两个子进程发信号SIGUSR1/SIGUSR2
       当收到发来的信号后，分别输出以下信息及信号的标号后终止
      	    Child process 1 is killed my parent：信号标号
	    Child process 2 is killed my parent：信号标号
       父进程等待两个子进程终止后，输出以下信息后终止
	Parent process exit;
*/
pid_t id,id1;

void fun(int sig)
{
	kill(id,SIGUSR1);
	kill(id1,SIGUSR2);	
}

void otherfun1(int sig)
{
	printf("Child process 1 is killed my parent：%d\n",sig);
}

void otherfun2(int sig)
{
	printf("Child process 2 is killed my parent：%d\n",sig);
}
int main()
{
	signal(SIGINT,fun);
	id=fork();
	if(id>0) 
	{
		id1=fork();
		if(id1==0) //第二个子进程
		{
			signal(SIGUSR2,otherfun2);
			pause();
			exit(2);
		}
	}
	else if(id==0) //第一个子进程
	{
		signal(SIGUSR1,otherfun1);
		pause();
		exit(1);
	}
	wait(NULL);
	wait(NULL);
	printf("Parent process exit!\n");
	return 0;
	
}