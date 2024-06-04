#include "myhead.h"

/*
	进程间通信：无名管道的使用
	无名管道用于父子进程间的通信
	双向通信
*/

int main()
{
	pid_t id;
	int ret;
	//定义数组，保存读端和写端的文件描述符
	int fd[2]; //fd[0]对应读端  fd[1]对应写端
	int otherfd[2];
	//定义数组
	char buf[100];
	char otherbuf[100];
	//创建两个无名管道
	ret=pipe(fd);
	if(ret==-1)
	{
		perror("创建第一个无名管道失败了\n");
		return -1;
	}
	ret=pipe(otherfd);
	if(ret==-1)
	{
		perror("创建第二个无名管道失败了\n");
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
			bzero(otherbuf,100);
			scanf("%s",buf);
			//把键盘输入的信息写入到无名管道
			write(fd[1],buf,strlen(buf));
			if(strcmp(buf,"quit")==0)
				break;
			
			//从无名管道里面读取信息
			read(otherfd[0],otherbuf,100);
			if(strcmp(otherbuf,"quit")==0)
				break;
			printf("儿子回复的信息是: %s\n",otherbuf);
		}
	}
	else if(id==0) //子进程
	{
		while(1)
		{
			bzero(buf,100);
			bzero(otherbuf,100);
			//读取无名管道中的信息
			read(fd[0],buf,100);
			if(strcmp(buf,"quit")==0)
				exit(0);
			printf("老爸给我发送的信息是: %s\n",buf);
			
			//子进程给父进程发送信息
			printf("请输入要发送给老爸的信息!\n");
			scanf("%s",otherbuf);
			write(otherfd[1],otherbuf,strlen(otherbuf));
			if(strcmp(otherbuf,"quit")==0)
				exit(0);
		}
	}
	
	//关闭无名管道
	close(fd[0]);
	close(fd[1]);
	close(otherfd[0]);
	close(otherfd[1]);
	wait(NULL);
	return 0;
}