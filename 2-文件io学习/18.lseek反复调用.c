#include "myhead.h"

/*
	1.txt当前内容是helloworldchinahehexixi
	总结：
	    第一：头脑不清晰--》画图分析
              最开始open打开(不能使用O_APPEND)，光标从第一个字符前面开始画  
        第二：read还是write光标都会变动
        第三：lseek从哪里开始移动光标(擦亮眼睛，看第三个参数和第二个参数)	
        第四：read/write都从光标后面一个位置开始		
*/
int main()
{
	int fd;
	char buf[20]={0};
	fd=open("1.txt",O_RDWR);
	
	//起始位置往后偏移10个字节
	lseek(fd,3,SEEK_SET); //没有搞清楚lseek最后一个参数干什么
	//测试读取
	read(fd,buf,2);
	printf("buf is: %s\n",buf); //lo
	
	//当前位置往后偏移3个字节
	lseek(fd,3,SEEK_CUR);  //没有搞清楚lseek最后一个参数干什么
	write(fd,"gec",3);
	
	//当前位置往前偏移5个字节
	bzero(buf,20);
	lseek(fd,5,SEEK_CUR);  //没有搞清楚lseek最后一个参数干什么
	read(fd,buf,4);
	printf("buf is: %s\n",buf); //ehex
	
	//起始位置往后偏移5个字节
	bzero(buf,20);
	lseek(fd,5,SEEK_SET); //没有搞清楚lseek最后一个参数干什么
	//测试读取
	read(fd,buf,5);
	printf("buf is: %s\n",buf); //worge	
	//关闭
	close(fd);
	return 0;
}