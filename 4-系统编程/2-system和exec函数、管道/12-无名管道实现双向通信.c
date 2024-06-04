#include "myhead.h"


int main()
{
	pid_t id;
	//定义个 数组
	int fd[2]={0};
	int fd1[2]={0};
	int ret;
	//创建无名管道
	ret=pipe(fd);
	if (ret==-1)
	{
		perror("pipe创建失败");
	}
	
	//我再创建一个无名管道来双向嘻嘻嘻
	ret=pipe(fd1);
	if (ret==-1)
	{
		perror("pipe创建失败");
	}
	//创建子进程
	id=fork();
	if(id<0)
	{
		perror("fork创建进程失败");
		return -1;
	}
	else if(id==0)
	{
		char buf[100]={0};
		//子进程
		while (1)
		{
			printf("子进程收到的数据是:");
			read(fd[0],buf,100);
			printf("%s:\n",buf);
			printf("输入发送给你爹的数据是:");
			scanf("%s",buf);
			write(fd1[1],buf,strlen(buf));
		}	
	}

	else if(id>0)
	{
		char buf[100]={0};
		//父进程
		while(1)
		{
			printf("请输入发给子进程的数据:\n");
			bzero(buf,sizeof(buf));
			scanf("%s",buf);
			write(fd[1],buf,strlen(buf));
			printf("父进程收到的数据是:");
			read(fd1[0],buf,100);
			printf("%s:\n",buf);
		}
		
	}
	return 0;
	
	
}