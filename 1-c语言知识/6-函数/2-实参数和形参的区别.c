#include <stdio.h>

//交换两个整数的值
int swap(int a,int b) //版本1采用的传值  int a=a   int b=b
{
	int temp;
	temp=a;
	a=b;
	b=temp;  //对形参a和b进行了交换，跟实参a，b没有任何关系
	return 0;
}

int otherswap(int *a,int *b) //版本2采用的传地址  int *a=&a   int *b=&b
{
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;  
	return 0;
}

int main()
{
	//故意让实参的名字跟形参的名字一样
	int a=100,b=666;
	//swap(a,b);
	otherswap(&a,&b);
	printf("交换之后: %d  %d\n",a,b);
	return 0;
}

 