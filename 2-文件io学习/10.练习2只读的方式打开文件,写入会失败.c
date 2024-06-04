#include "myhead.h"
/*
	用O_RDONLY配合写入文件看看是否能够写入成功 
    不能，只读的方式打开文件，此时不能写入
*/
int main()
{
	int fd;
	//定义变量保存write返回值
	ssize_t ret;
	fd=open("1.txt",O_RDONLY);  //只读的方式打开文件，此时不能写入
	if(fd==-1)
	{
		printf("打开文件失败了!\n");
		return -1;
	}
	ret=write(fd,"helloworld",strlen("helloworld"));
	printf("write的返回值是: %ld\n",ret);
	//没有主动写close--》linux在主函数退出的时候会自动帮你把所有的文件关闭
	close(fd);
	return 0;
}