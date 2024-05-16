#include <stdio.h>

/*
二级指针存的是一级指针的地址值
这个肯定看操作系统的
比如64位系统的内存地址值就是8个字节
32位系统的内存地址值就是4个字节
*/

int main()
{
	int a=789;
	double b=45.69;
	char c[10]="hello";
	
	//定义三种不同类型的二级指针
	int *p1=&a;
	double *p2=&b;
	char *p3=c;
	int **q1=&p1;
	double **q2=&p2;
	char **q3=&p3;
	
	//无论是一级指针还是二级指针，本身的大小都是8个字节(64位系统)
	printf("sizeof(p1)  %ld\n",sizeof(p1));
	printf("sizeof(q1)  %ld\n",sizeof(q1));
	printf("sizeof(p2)  %ld\n",sizeof(p2));
	printf("sizeof(q2)  %ld\n",sizeof(q2));
	printf("sizeof(p3)  %ld\n",sizeof(p3));
	printf("sizeof(q3)  %ld\n",sizeof(q3));
	
	//验证二级指针+1  -1 偏移多少字节
	printf("q1存放的地址: %p\n",q1);
	printf("q1+1存放的地址: %p\n",q1+1);
	printf("q1-1存放的地址: %p\n",q1-1);
	
	printf("q2存放的地址: %p\n",q2);
	printf("q2+1存放的地址: %p\n",q2+1);
	printf("q2-1存放的地址: %p\n",q2-1);
	
	printf("q3存放的地址: %p\n",q3);
	printf("q3+1存放的地址: %p\n",q3+1);
	printf("q3-1存放的地址: %p\n",q3-1);
	
	
}