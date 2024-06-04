#include "myhead.h"

int main()
{
	int fd; 
	//新建一个记事本--》O_CREAT|O_EXCL 1.txt存在就不新建并且返回-1表示新建失败
	//                  O_CREAT|O_EXCL 1.txt不存在就立马新建一个
	//fd=open("1.txt",O_RDONLY|O_CREAT|O_EXCL); 
	
	//新建一个记事本--》O_CREAT|O_TRUNC 1.txt存在,立马清空覆盖掉1.txt
	//                  O_CREAT|O_TRUNC 1.txt不存在就立马新建一个
	fd=open("1.txt",O_RDONLY|O_CREAT|O_TRUNC);
	if(fd==-1)
	{
		printf("新建记事本失败了!\n");
		return -1; //退出主函数
	}
}