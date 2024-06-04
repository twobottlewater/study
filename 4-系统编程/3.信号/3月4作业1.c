#include "myhead.h"

/*
	进程间通信：无名管道的使用
	无名管道用于父子进程间的通信
	双向通信
*/

int main()
{
	pid_t id,id1;
	int ret;
	//定义数组，保存读端和写端的文件描述符
	int fd[2]; //fd[0]对应读端  fd[1]对应写端
	//定义数组
	char buf[100]={0};
	//创建一个无名管道
	ret=pipe(fd);
	if(ret==-1)
	{
		perror("创建第一个无名管道失败了\n");
		return -1;
	}
	
	//创建两个子进程
	id=fork();
	if(id>0) //父进程
	{
		id1=fork();
		if(id1==0) //第二个子进程
		{
			bzero(buf,100);
			read(fd[0],buf,100);
			printf("第二个子进程读取的信息: %s\n",buf);
			write(fd[1],"hello world",11);
			exit(2);
		}
	}
	else if(id==0) //第一个子进程
	{
		write(fd[1],"hello",5);
		exit(1);
	}
	
	sleep(2);
	//父进程读取最后的信息
	read(fd[0],buf,100);
	printf("父进程最后读取的信息是: %s\n",buf);
	wait(NULL);
	wait(NULL);
	//关闭无名管道
	close(fd[0]);
	close(fd[1]);
	return 0;
}