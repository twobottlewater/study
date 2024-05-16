#include <stdio.h>
 
int main()
 {
	int i,j,n,k;
	printf("请输入图案数目:");
	scanf("%d",&n);
	
	for(i=1;i<=(n+1)/2;i++)
	{
		//先打印空格
		for(j=0;j<(n+1)/2-i;j++)
			printf(" ");
		//在打星号
		for(j=0;j<2*i-1;j++)
			printf("*");
		//打印完就空格
		printf("\n");
	}
	//打印下半部分
	
	for(i=1;i<=(n/2);i++)
	{
		//先打印空格
		for(j=0;j<i;j++)
			printf(" ");
		//再打印星号  星号加行数=n-变量
		for(j=0;j<n-i-i;j++)
			printf("*");
	printf("\n");
	}
  }
	
	
