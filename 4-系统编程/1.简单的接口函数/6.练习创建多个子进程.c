#include "myhead.h"

/*
	练习：创建多个子进程
*/

int main()
{
	pid_t id,id1;
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
			exit(2);
		}
	}
	else if(id==0) //第一个子进程
	{
		printf("杀毒!\n");
		exit(1);
	}
	
	printf("父进程执行软件升级!\n");
	//回收两个子进程
	ret=wait(&status);
	printf("我目前回收的子进程是: %d,退出值: %d\n",ret,(status&0xff00)>>8);
	ret=wait(&status);
	printf("我目前回收的子进程是: %d,退出值: %d\n",ret,(status&0xff00)>>8);
	return 0;
}