#include <stdio.h>



#define N 3 
#define Y(n) ((N+1)*n)
//宏定义是多行的要加上续行符号
#define BIG(a,b) if(a>b) printf("a是较大的\n");\
else printf("b是较大的\n");




void main()
{
	printf("%d\n",2*(N+Y(5+1)));  //2*(3+((3+1)*5+1))
								//			2*	(3+(21))
								//48
	int n1=78;
	int n2=96;
	BIG(n1,n2);
}