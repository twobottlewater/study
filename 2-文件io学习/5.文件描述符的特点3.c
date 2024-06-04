#include "myhead.h"
/*
	第三个：文件描述符最大值是多少--》0---1023
*/
int main()
{
	int i;
	int fd;
	//循环打开同一个记事本多次，来测试文件描述符最大可以是多少
	for(i=0; i<5000; i++)
	{
		fd=open("1.txt",O_RDWR);
		if(fd==-1)
		{
			printf("打开文件1失败了!\n");
			return -1;
		}
		printf("现在文件描述符是: %d\n",fd);
	}
	
	
}