#include "myhead.h"

/*
	演示signal捕捉SIGINT信号做收尾工作
*/
int fd;
void fun(int sig)
{
	printf("当你输入ctrl+c强行退出程序!\n");
	//关闭有名管道
	close(fd);
	exit(0);
}

int main()
{
	int ret;
	char buf[100];
	
	//判断有名管道是否已经存在
	if(access("/home/gec/myfifo",F_OK)!=0) //不存在
	{
		//创建一个有名管道
		ret=mkfifo("/home/gec/myfifo",0777);
		if(ret==-1)
		{
			perror("新建有名管道失败了!\n");
			return -1;
		}
	}
			
	//打开刚才新建的有名管道--》open
	fd=open("/home/gec/myfifo",O_RDWR);
	if(fd==-1)
	{
		perror("打开有名管道失败了!\n");
		return -1;
	}
	
	signal(SIGINT,fun);
	//使用有名管道收发信息--》read、write
	while(1)
	{
		printf("请输入要发送给p2的信息!\n");
		bzero(buf,100);
		scanf("%s",buf);
		//发送给p2
		write(fd,buf,strlen(buf));
	}
	return 0;
}