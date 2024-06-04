#include "myhead.h"

/*
	execle的使用
	实现在一个进程中调用执行另外一个进程
	exec函数族：
	    l --》参数以列表的形式逐一列举
		p --》表示从系统的环境变量中去查找要执行的shell命令或者程序
		e --》执行程序的时候，可以顺便设置那个程序的环境变量
*/

int main()
{
	char *evp[]={"PATH=/home/gec",NULL};
	//execle("/bin/ls","ls","-l",NULL,evp);

	
	execle("/mnt/hgfs/share/hello","./hello","最炫民族风",NULL,evp);
}