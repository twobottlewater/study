#include "myhead.h"

/*
	sigqueue的使用
*/


int main(int argc,char **argv)
{
	union sigval val;
	val.sival_int=666;
	
	//发送信号，同时给另外一个进程发送一个整数
	sigqueue(atoi(argv[1]),atoi(argv[2]),val);
	return 0;
}