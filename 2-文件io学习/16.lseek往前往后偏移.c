#include "myhead.h"

/*
	1.txt当前内容是hello
*/
int main()
{
	int fd;
	char buf[20]={0};
	fd=open("1.txt",O_RDWR);
	
	//起始位置往后/往后偏移100个字节
	//lseek(fd,100,SEEK_SET); //起始位置往后偏移，中间留空格
	//lseek(fd,-100,SEEK_SET);  //起始位置无法往前偏移
	
	//先读取5个字节
	read(fd,buf,5);
	printf("buf is: %s\n",buf);
	
	//当前位置往后/往后偏移个字节
	lseek(fd,-2,SEEK_CUR); //当前位置往前偏移
	
	//先读取3个字节
	bzero(buf,20);
	read(fd,buf,3); 
	printf("buf is: %s\n",buf);
	
	//关闭
	close(fd);
	return 0;
}