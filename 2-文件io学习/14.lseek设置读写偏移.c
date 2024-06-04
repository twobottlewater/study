#include "myhead.h"
/*
	1.txt中存放了helloworld
	我不要hello，我要world
*/
int main(int argc,char **argv) //主函数传参
{
	int fd;
	char buf[20]={0};
	//打开文件
	fd=open("1.txt",O_RDWR);
	if(fd==-1)
	{
		printf("打开文件失败!\n");
		return -1;
	}
	
	//跳过最前面的5个字节，从第6个字节开始读取
	lseek(fd,5,SEEK_SET); //从起始位置往后跳(偏移)5个字节
	
	//再来读取文件，从第6个字节开始读取
	read(fd,buf,5);
	printf("我读取的内容是: %s\n",buf);
	
	//关闭文件
	close(fd);
	return 0;
}