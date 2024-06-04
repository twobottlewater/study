#include "myhead.h"

/*
	展示信号有啥用
*/

int main()
{
	while(1)
	{
		printf("当前进程正在运行,你能把我怎么样! ID %d\n",getpid());
		sleep(1);
	}
	return 0;
}