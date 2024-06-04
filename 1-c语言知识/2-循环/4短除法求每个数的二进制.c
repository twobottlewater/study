#include <stdio.h>
 
int main()
 {
	int i;
	int num;
	printf("请输入一个数\n");
	scanf("%d",&num);
	//用num不断余2,余数倒过来就二进制
	while(num>1)
	{
		printf("当前求出来的二进制位:%d\n",num%2);
		
		num/=2;
		
	}
	printf("当前求出来的二进制位:%d\n",num);
  }
	
	
