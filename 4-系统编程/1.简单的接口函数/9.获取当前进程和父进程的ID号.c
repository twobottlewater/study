#include "myhead.h"

/*
	获取当前进程以及父进程的ID号
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
		printf("第一个子进程ID： %d\n",id);
		//生第二个
		id1=fork();
		if(id1==0) //第二个子进程
		{
			printf("扫描漏洞!第二个子进程自己的ID：%d,它老爸是: %d\n",getpid(),getppid());
			exit(2);
		}
		else if(id1>0) //父进程
		{
			printf("第二个子进程ID： %d\n",id1);
			//生第三个子进程
			id2=fork(); 
			if(id2==0) //第三个子进程
			{
				printf("清理垃圾!第三个子进程自己的ID：%d,它老爸是: %d\n",getpid(),getppid());
				exit(3);
			}
		}
	}
	else if(id==0) //第一个子进程
	{
		printf("杀毒,第一个子进程自己的ID：%d,它老爸是: %d!\n",getpid(),getppid());
		exit(1);
	}
	
	printf("父进程执行软件升级!\n");
	//回收三个子进程-->假设我按照 2  3  1来回收
	ret=waitpid(id1,&status,0);
	printf("我目前回收的子进程是: %d,退出值: %d\n",ret,(status&0xff00)>>8);
	ret=waitpid(id2,&status,0);
	printf("我目前回收的子进程是: %d,退出值: %d\n",ret,(status&0xff00)>>8);
	ret=waitpid(id,&status,0);
	printf("我目前回收的子进程是: %d,退出值: %d\n",ret,(status&0xff00)>>8);
	return 0;
}