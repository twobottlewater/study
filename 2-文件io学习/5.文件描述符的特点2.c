#include "myhead.h"
/*
	第二个：linux系统总是把目前没有被占用的最小的文件描述符分配给你
*/
int main()
{
	
	int fd1,fd2,fd3;
	//打开记事本
	fd1=open("1.txt",O_RDWR);
	if(fd1==-1)
	{
		printf("打开文件1失败了!\n");
		return -1;
	}
	//打印文件描述符
	printf("打开的第一个文件，文件描述符是:%d\n",fd1);
	
	fd2=open("2.txt",O_RDWR);
	if(fd2==-1)
	{
		printf("打开文件2失败了!\n");
		return -1;
	}
	//打印文件描述符
	printf("打开的第二个文件，文件描述符是:%d\n",fd2);
	
	//偷偷摸摸关闭2.txt
	close(fd2);  //把文件描述符释放--》把数组对应的位置下标腾出来让给其他文件使用
	
	fd3=open("3.txt",O_RDWR);
	if(fd3==-1)
	{
		printf("打开文件3失败了!\n");
		return -1;
	}
	//打印文件描述符
	printf("打开的第三个文件，文件描述符是:%d\n",fd3);
}