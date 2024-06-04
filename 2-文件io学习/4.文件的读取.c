#include "myhead.h"

int main()
{
	int fd;
	//定义数组存放读取的内容
	char buf[20]={0};
	//定义变量保存read的返回值
	ssize_t ret;
	
	//打开记事本
	fd=open("1.txt",O_RDWR);
	if(fd==-1)
	{
		printf("打开文件失败了!\n");
		return -1;
	}
	
	//读取文件内容
	ret=read(fd,buf,20); //读取20个字节的数据存放到buf中
	printf("当前read成功读取的字节数是: %ld\n",ret);
	//验证打印读取的内容
	printf("刚才你读取的文件内容是： %s\n",buf);
	
	//接着再读取
	ret=read(fd,buf,20); //读取20个字节的数据存放到buf中
	printf("当前read成功读取的字节数是: %ld\n",ret);

}