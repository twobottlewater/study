#include "myhead.h"

int main(int argc,char **argv)
{
	int ret,fd;
	char buf[10]={0};
	fd=open("new.txt",O_RDWR);
	if(fd==-1)
	{
			printf("打开文件失败\n");
			return -1;
		}
		
		//要读取文件中某个位置
		lseek(fd,10,SEEK_SET);
		
		write(fd,"niubi!",6);
		
		//收尾
		close(fd);
	return 0;		
		
		
		
		
}