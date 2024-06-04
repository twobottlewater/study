#include <stdio.h>

int main()
{
	int a;
	int b;
	
	printf("请输入两个数\n");
	scanf("%d %d",&a,&b);
	int result=(a>b)?a:b;
	printf("ok了:%d\n",result);
 

}