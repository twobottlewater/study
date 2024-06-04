#include "myhead.h"

/*
	execv的使用
	实现在一个进程中调用执行另外一个进程
	exec函数族：
	    l --》参数以列表的形式逐一列举
		p --》表示从系统的环境变量中去查找要执行的shell命令或者程序
		e --》执行程序的时候，可以顺便设置那个程序的环境变量
		v --》跟l区分就可以，v表示参数用指针数组存放
*/

int main()
{
	//char *arg[]={"ls","-l",NULL};
	//execv("/bin/ls",arg);

	char *arg[]={"./hello","最炫民族风",NULL};
	execv("/mnt/hgfs/share/hello",arg);
}