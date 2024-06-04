#include <stdio.h>
#include <string.h>
int main()
{
	

	int *p; //定义一个没有被定义的指针
	printf("666\n");
	*p=666;
	//打印首地址
	printf("指针p地址中存放的数据是: %d\n",*p);
	printf("777\n");
	
	return 0;
}