#include "myhead.h"



int main()
{
	pid_t id;
	printf("孙悟空运行\n");
	//创建子进程
	id=fork();
	if(id<0)
	{
		perror("fork");
		return -1;
	}
	else if(id==0)
	{
		//子进程
		while (1)
		{printf("我是猴子\n");}
		

	}

	else if(id>0)
	{
		//父进程
		while (1)
		{printf("我是孙悟空\n");}
		
	}
	return 0;
	
}