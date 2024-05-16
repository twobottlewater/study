#include <stdio.h>
#define INTP int *  //宏定义--等价于int *
typedef int * intp; //给int *取了别名叫做intp
/*
	intp p,*q; //很多同学被这种写法迷惑
	//老师支招
	intp p;
	intp *q;

*/

int main()
{
	int a=99;
	int b=78;
	intp p,*q;  
	INTP p1,*q1;  //int *p1,*q1;
	
	//证明p是一级指针
	p=&a;
	
	//证明q是二级指针
	q=&p;
	
	//证明p1是一级指针
	p1=&a;
	//证明q1是一级指针
	q1=&b;
	
}