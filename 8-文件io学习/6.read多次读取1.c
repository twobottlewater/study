#include "myhead.h"
/*
	read多次读取同一个文件
	open打开文件，默认光标都是从起始位置开始
	下面这段代码如果你重复多次运行，每次只能读取到最前面的5个字节
*/
int main()
{
	int fd;
	char buf[20]={0};
	fd=open("1.txt",O_RDWR);
	if(fd==-1)
	{
		printf("打开文件失败了!\n");
		return -1;
	}
	
	//读取文件内容
	read(fd,buf,5);
	printf("刚才读取的内容是： %s\n",buf);
	
	//没有主动写close--》linux在主函数退出的时候会自动帮你把所有的文件关闭

}