#include "myhead.h"
/*
	文件的写入:注意第三个参数
	返回值：成功：第三个参数count写多少，返回值就是多少
*/
int main()
{
	int fd;
	//定义变量保存write返回值
	ssize_t ret;
	fd=open("1.txt",O_RDWR);
	if(fd==-1)
	{
		printf("打开文件失败了!\n");
		return -1;
	}
	//情况1：第三个参数比你实际内容长度小
	//  第三个参数count写2，返回值就是2
	//ret=write(fd,"helloworld",2);
	//情况2：第三个参数比你实际内容长度大
	//  第三个参数count写200，返回值就是200
	//  helloworld根本不够200个字节，write会自动填充190个字节的垃圾数写入到记事本
	ret=write(fd,"helloworld",200);
	printf("write的返回值是: %ld\n",ret);
	//没有主动写close--》linux在主函数退出的时候会自动帮你把所有的文件关闭
	close(fd);
	return 0;
}