#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>


int main()
{ 
	int a[8];
	float b[3];
	double c[9];
	char d[10];
	
	/*
		定义数组指针，指向a
		定义数组指针的公式：
		      指向某个数组的指针
              类型 (*指针名)[数组元素个数]
	*/

	/*
	int (*p)[8]=&a; //a的类型是int *  &a的类型是int (*)[8]
	int (*p)[8];
	p=&a;
	*/

	float (*p1)[3]=&b;
	double (*p2)[9]=&c;
	char (*p3)[10]=&d;
	return 0;
}
  


