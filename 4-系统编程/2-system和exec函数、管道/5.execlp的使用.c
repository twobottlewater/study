#include "myhead.h"

/*
	execlp的使用
	实现在一个进程中调用执行另外一个进程
	exec函数族：
	    l --》参数以列表的形式逐一列举
		p --》表示从系统的环境变量中去查找要执行的shell命令或者程序
*/

int main()
{
	//execlp("ls","ls","-l",NULL);
	//execlp("rm","rm","/home/gec/myhead.h",NULL);
	
	execlp("hello","./hello","最炫民族风",NULL);
}