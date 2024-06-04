#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	printf("各位同学你等会看不到这句话!");	
	exit(0);  //结束程序的时候，会帮你刷新缓冲区
}