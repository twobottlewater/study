#include "myhead.h"

/*
	1.txt当前内容是hello
*/
int main()
{
	int fd;
	char buf[20]={0};
	fd=open("1.txt",O_RDWR);
	
	//起始位置往后/往后偏移10个字节
	//lseek(fd,10,SEEK_SET); //起始位置往后偏移，中间留空格
	lseek(fd,-10,SEEK_SET); //起始位置往前偏移，没有任何意义
	//测试写入
	//write(fd,"world",5);
	//测试读取
	read(fd,buf,5);
	printf("buf is: %s\n",buf);
		
	//关闭
	close(fd);
	return 0;
}