#include "myhead.h"

/*
	进程间通信：有名管道的使用
	有名管道和无名管道区别
	    区别1：有名管道会生成管道文件，无名管道没有(只有文件描述)
		区别2：有名管道只有一个文件描述符(既可以读也可以写)
	进程p2的代码
*/

int main()
{
	int ret;
	int fd;
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
	
	//使用有名管道收发信息--》read、write
	while(1)
	{
		bzero(buf,100);
		//读取有名管道中的数据
		read(fd,buf,100);
		printf("p1给我发的信息是: %s\n",buf);
	}
	
	//关闭有名管道
	close(fd);
	return 0;
}