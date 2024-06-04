#include "myhead.h"

int main()
{
	int fd; 
	//打开一个记事本
	fd=open("1.txt",O_RDONLY); //我以只读的方式打开1.txt
	if(fd==-1)
	{
		printf("打开记事本失败了!\n");
		return -1; //退出主函数
	}
}