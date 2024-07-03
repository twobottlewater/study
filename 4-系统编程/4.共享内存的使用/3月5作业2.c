#include "myhead.h"

/*
	 用信号模拟司机售票员：创建子进程代表售票员，父进程代表司机，
		1：售票员捕捉SIGINT(代表开车)，发SIGUSR1 给司机，司机捕捉到SIGUSR1 信

号后打印“move to next station”
		2: 售票员捕捉SIGQUIT(代表靠站)，发SIGUSR2 给司机，司机捕捉到SIGUSR2 信

号后打印“stop the bus”
		3: 司机捕获到SIGTSTP（车到总站），发SIGUSR1给售票员，
		   售票员捕捉到SIGUSR1信号后打印“all get off the bus”，全部进程结束
*/
pid_t id;
int flag=1; //用于结束掉父子进程

//跟售票员相关的响应函数
void movebus(int sig)
{
	if(sig==SIGINT)
		//发送SIGUSR1给司机
		kill(getppid(),SIGUSR1);
	if(sig==SIGQUIT)
		//发送SIGUSR2给司机
		kill(getppid(),SIGUSR2);	
	if(sig==SIGUSR1)
	{
		printf("all get off the bus!\n");
		flag=0;
	}
		
}
//跟司机相关的响应函数
void drivebus(int sig)
{
	if(sig==SIGUSR1)
		printf("move to next station！\n");
	if(sig==SIGUSR2)
		printf("stop the bus！\n");
	if(sig==SIGTSTP)
	{
		kill(id,SIGUSR1);
		flag=0;
	}
}
int main()
{
	id=fork();
	if(id>0) //父进程代表司机
	{
		printf("司机ID：%d\n",getpid());
		signal(SIGUSR1,drivebus);
		signal(SIGUSR2,drivebus);
		signal(SIGTSTP,drivebus);
		while(1)
		{
			if(flag==0)
				break;
		}
	}
	else if(id==0) //子进程代表售票员
	{
		printf("售票员ID：%d\n",getpid());
		signal(SIGINT,movebus);
		signal(SIGQUIT,movebus);
		signal(SIGUSR1,movebus);
		while(1)
		{
			if(flag==0)
				break;
		}
		exit(0);
	}
	wait(NULL);
	return 0;
	
}