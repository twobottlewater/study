#include "myhead.h"

/*
	exec和system的区别
	
*/

int main()
{
	
	//execl("/bin/ls","ls","-l",NULL);
	system("ls -l");
	//当前进程还要干别的事情
	printf("主函数继续往后执行!\n");
	return 0;
}