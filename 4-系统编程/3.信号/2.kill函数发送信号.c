#include "myhead.h"

/*
	kill函数发送信号
*/

int main(int argc,char **argv)
{
	//发送的进程的id   发送的是kill命令信号啊编码
	kill(atoi(argv[1]),atoi(argv[2]));
	return 0;
}