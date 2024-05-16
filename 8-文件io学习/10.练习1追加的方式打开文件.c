#include "myhead.h"
/*
	如果你open(不使用O_APPEND) --》光标就在起始位置
    如果你open(使用O_APPEND) --》光标就在末尾位置
*/
int main()
{
	int fd;
	//定义变量保存write返回值
	ssize_t ret;
	//fd=open("1.txt",O_RDWR|O_APPEND);
	fd=open("1.txt",O_RDWR);
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