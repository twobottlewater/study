#include "myhead.h"
/*
	第一个：0 1 2已经默认被键盘，液晶屏占用了，只能从3开始分配
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
	
	fd3=open("3.txt",O_RDWR);
	if(fd3==-1)
	{
		printf("打开文件3失败了!\n");
		return -1;
	}
	//打印文件描述符
	printf("打开的第三个文件，文件描述符是:%d\n",fd3);
	
	

}