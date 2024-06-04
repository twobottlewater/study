#include "myhead.h"

/*
	lseek求文件大小
*/
int main()
{
	int fd;
	off_t ret;
	char buf[20]={0};
	fd=open("1.txt",O_RDWR);
	
	//把偏移挪到末尾位置
	ret=lseek(fd,0,SEEK_END); //没有搞清楚lseek最后一个参数干什么
	printf("lseek返回值表示当前偏移位置(末尾)距离文件开头的字节数: %ld\n",ret);
		
	//关闭
	close(fd);
	return 0;
}