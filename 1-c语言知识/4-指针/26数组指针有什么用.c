#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>


int main()
{ 
	int a[8]={25,56,89};
	int b[8]={26,666,77};
	int c[8]={98,46,59};
	//定义数组指针，指向a
	/*
		定义数组指针的公式：
		      指向某个数组的指针
              类型 (*指针名)[数组元素个数]
             数组指针可以让我们指向相同类型的数组
	*/
	int (*p)[8]=&a; //a的类型是int *  &a的类型是int (*)[8]
	p=&b;
	p=&c;

	// printf("%d %d %d\n",**p,**(p+1),**(p+2));
	
	for (size_t i = 0; i < 8; i++)
	{
		printf("%d\n",**(p+i));
		/* code */
	}
	

	/*打印出来的明显是
	由此可知*p这个指针虽然是int *p[8] 也就是他可以存8个int[8]数组的首地址
	98
	26
	25*/

	return 0;
}
  


