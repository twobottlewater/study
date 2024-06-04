#include<stdio.h>

int main()
{

	while(1)
	{
		printf("111\n");
		
		while(1)
		{
			printf("222\n");
			
			int v = 6;
			
			if(v == 6)
			{
				printf("333\n");
				continue;  //当遇到这个关键字的时候，此时程序不会往下面走了，而是从最近一层循环又开始运行
				printf("444\n");
			}
			
			printf("555\n");
		}
		
	}
	

	
	return 0;
}