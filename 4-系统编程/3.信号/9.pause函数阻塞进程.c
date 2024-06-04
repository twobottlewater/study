#include "myhead.h"

/*
	pause可以阻塞进程，让外界有充足的时间可以给当前进程发送信号
*/

int main()
{
	printf("当前进程正在运行,你能把我怎么样! ID %d\n",getpid());
	pause();
	return 0;
}