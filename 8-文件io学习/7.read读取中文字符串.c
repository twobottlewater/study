#include "myhead.h"
/*
	UTF-8编码：汉字占3个字节
	GB2312:汉字占2个字节
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
	read(fd,buf,3);
	printf("刚才读取的内容是： %s\n",buf);
	
	
	
	
	//没有主动写close--》linux在主函数退出的时候会自动帮你把所有的文件关闭

}