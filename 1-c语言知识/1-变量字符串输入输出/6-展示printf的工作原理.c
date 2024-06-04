#include <stdio.h>
#include <unistd.h>

int main()
{
	int i=0;
	//定义变量，统计循环次数
	int n=0;
	//演示把缓冲区挤爆
	for(;i<25; i++)  //彭老师的ubuntu临界值是25,25次循环，缓冲区就满了
	{
		printf("各位同学你等会看不到这句话 %d!",n);
		n++;
	}
	_exit(0);  //结束程序的时候，不会帮你刷新缓冲区
}