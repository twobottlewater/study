#include "myhead.h"

/*
	waitpid非阻塞等待
*/

int main()
{
	pid_t id,id1,id2;
	pid_t ret;
	int i;
	int status;
	//先生第一个
	id=fork();
	if(id>0) //父进程
	{
		//生第二个
		id1=fork();
		if(id1==0) //第二个子进程
		{
			printf("扫描漏洞!\n");
			sleep(2);
			exit(2);
		}
		else if(id1>0) //父进程
		{
			//生第三个子进程
			id2=fork(); 
			if(id2==0) //第三个子进程
			{
				printf("清理垃圾!\n");
				exit(3);
			}
		}
	}
	else if(id==0) //第一个子进程
	{
		printf("杀毒!\n");
		exit(1);
	}
	
	printf("父进程执行软件升级!\n");
	//回收三个子进程-->假设我按照 2  3  1来回收
	ret=waitpid(id1,&status,WNOHANG);
	printf("我目前回收的子进程是: %d,退出值: %d\n",ret,(status&0xff00)>>8);
	ret=waitpid(id2,&status,0);
	printf("我目前回收的子进程是: %d,退出值: %d\n",ret,(status&0xff00)>>8);
	ret=waitpid(id,&status,0);
	printf("我目前回收的子进程是: %d,退出值: %d\n",ret,(status&0xff00)>>8);
	return 0;
}