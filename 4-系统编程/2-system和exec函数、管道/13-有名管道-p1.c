#include "myhead.h"


int main()
{

	int ret;
    int fd;

	if (access("/home/gec/myfifo",F_OK)!=0)//不存在
	{
		/* code */
		ret=mkfifo("/home/gec/myfifo",0666);
		if (ret==-1)
		{
			perror("mkfifo创建失败");

		}
	}

	//2.打开有名管道
    fd=open("/home/gec/myfifo",O_RDWR);
	if (fd==-1)
    {
        perror("打开管道失败");
    }

	char buf[100]={0};     
	while (1)
	{   
		printf("请输入要发送给p2的数据：");
		bzero(buf,sizeof(buf));
		scanf("%s",buf);
		write(fd,buf,strlen(buf));
	}	
	close(fd);
	return 0;

	
}