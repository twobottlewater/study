#include "myhead.h"

/*
	进程间通信：无名管道的使用
	无名管道用于父子进程间的通信
	单向通信，父进程从键盘输入字符串发送给子进程
*/

int main()
{
	pid_t id;
	int ret;
	//定义数组，保存读端和写端的文件描述符
	int fd[2]; //fd[0]对应读端  fd[1]对应写端
	//定义数组
	char buf[100];
	//创建一个无名管道
	ret=pipe(fd);
	if(ret==-1)
	{
		perror("创建无名管道失败了\n");
		return -1;
	}
	//创建子进程
	id=fork();
	if(id>0) //父进程
	{
		while(1)
		{
			printf("爹地，请输入要发送给儿子的信息!\n");
			bzero(buf,100);
			scanf("%s",buf);
			//把键盘输入的信息写入到无名管道
			write(fd[1],buf,strlen(buf));
		}
	}
	else if(id==0) //子进程
	{
		while(1)
		{
			bzero(buf,100);
			//读取无名管道中的信息
			read(fd[0],buf,100);
			printf("老爸给我发送的信息是: %s\n",buf);
		}
	}
	return 0;
}