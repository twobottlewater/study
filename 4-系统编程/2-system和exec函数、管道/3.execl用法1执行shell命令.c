#include "myhead.h"

/*
	execl执行shell命令
	实现在一个进程中调用执行另外一个进程
	exec函数族：
	    l --》参数以列表的形式逐一列举
*/

int main()
{
	//execl("/bin/ls","ls","-l",NULL);
	//cp ./myhead.h  /home/gec
	execl("/bin/cp","cp","./myhead.h","/home/gec",NULL);
}