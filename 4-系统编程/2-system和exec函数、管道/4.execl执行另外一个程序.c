#include "myhead.h"

/*
	execl执行另外一个程序
	实现在一个进程中调用执行另外一个进程
	exec函数族：
	    l --》参数以列表的形式逐一列举
*/

int main()
{
	execl("/mnt/hgfs/share/hello","./hello","科目三",NULL);
}