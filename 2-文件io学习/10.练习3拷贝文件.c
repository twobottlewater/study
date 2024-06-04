#include "myhead.h"
/*
	练习3：拷贝文件
	数组buf定义大一点，循环次数会少一些，拷贝的速度更快，尤其是拷贝大文件
*/
int main()
{
	int fd,newfd;
	//定义数组存放读取到的内容
	char buf[2000];  //局部变量，栈空间(8M左右)
	//定义变量保存read返回值
	ssize_t ret;
	
	//打开源文件
	fd=open("1.txt",O_RDONLY);  //只读的方式打开文件，此时不能写入
	if(fd==-1)
	{
		printf("打开文件失败了!\n");
		return -1;
	}
	
	//新建目标文件--》只写的方式打开，新建，文件存在就清空覆盖
	newfd=open("/home/gec/new.txt",O_WRONLY|O_CREAT|O_TRUNC);  
	if(newfd==-1)
	{
		printf("新建文件失败了!\n");
		return -1;
	}
	
	//循环读取源文件的内容，写入到目标文件中
	while(1)
	{
		//读取源文件
		ret=read(fd,buf,2000); 
		printf("成功读取的字节数： %ld\n",ret);
		if(ret==0) //说明文件读取完毕了
			break; //退出循环
		//把读取的内容写入目标文件
		write(newfd,buf,ret);
	}
	
	//关闭文件
	close(fd);
	close(newfd);
	return 0;
}