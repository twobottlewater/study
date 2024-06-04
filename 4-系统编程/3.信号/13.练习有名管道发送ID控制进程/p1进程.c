#include "myhead.h"

/*
	p1进程把自己的id号通过有名管道发送给p2进程，p2进程使用kill函数发送信号控制p1暂停，继续，退出
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
	
	//使用有名管道把自己的ID发给p2
	pid_t id=getpid();
	write(fd,&id,sizeof(id));

	while(1)
	{
		printf("进程1接着往后执行!\n");
		sleep(1);
	}
	
	//关闭有名管道
	close(fd);
	return 0;
}