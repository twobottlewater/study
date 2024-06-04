#include <stdio.h>
 
int main()
 {
	int i;
	int num;
	int temp;
	printf("请输入一个数\n");
	scanf("%d",&num);
	//用num不断余2,余数倒过来就二进制
	for(i=0;i<32;i++)
	{
		temp=num&(0x1<<i);
		temp=temp>>i;
		printf("%d当前求出来的二进制位:%d\n",num,temp);
		
		
		
	}
	
  }
	
	
