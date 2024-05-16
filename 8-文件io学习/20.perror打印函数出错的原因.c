#include "myhead.h"

/*
	perror打印函数出错的原因
*/
int main()
{
	int fd;
	fd=open("/home/gec/haha.txt",O_RDWR);
	if(fd==-1)
	{
		//很笼统，没有告诉用户出错的原因，只是打印了一句废话
		//printf("打开记事本失败!\n");
		perror("打开记事本失败!\n"); //可以告诉程序员错误的原因
		//linux的errno.h中有定义全局变量  int errno用来记录保存当前的错误码
		printf("open函数调用失败了，失败的原因对应的数字编号(错误码)是:%d\n",errno);
		return -1;
	}

		
	//关闭
	close(fd);
	return 0;
}