#include "myhead.h"





int main()
{
	//定义数组存一部分数据
	int buf[10000];
	int ret;
	//定义的文件描述符
	int srcfd,destfd;
	//获取文件描述符，打开文件
	srcfd=open("1.mp4",O_RDWR);
	if(srcfd==-1)
	{printf("打开文件失败\n");\
		return -1;
		}
		
		
	//新建目标文件
	destfd=open("/home/gec/2.mp4",O_RDWR|O_EXCL|O_CREAT);
	if(destfd==-1)
	{
		printf("新建文件失败了\n");
		return -1;
		}
		
		while(1)
		{
			bzero(buf,10000);
			//读取源文件数据
			ret=read(srcfd,buf,10000);
			if(ret==0)
			break;
			//把读到的数据立马写入目标文件中
			write(destfd,buf,ret);
		
			
			
			}
			
	close(srcfd);
	close(destfd);
	return 0;	
}