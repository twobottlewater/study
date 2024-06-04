#include <stdio.h>
#include <string.h>
int main()
{
	int a=789;

	int *p; //定义一个没有被定义的指针
	p=&a;
	//打印首地址
	printf("指针p地址中存放的数据是: %p\n",&a);
	printf("指针p地址中存放的数据是: %p\n",p);//p变量的存的是a的首地址
	printf("指针p地址中存放的数据是: %d\n",*p);//*p存的是p这个指针的首地址
	printf("指针p地址中存放的数据是: %d\n",a);//*p存的是p这个指针的首地址
	
	return 0;
}