#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()  
{
	int mun;
	printf("请输入一个整数!\n");
	scanf("%d",&mun);
	while (mun!=0)
	{
		/* code */
		printf("刚刚输入的正整数,由高到低分别是:%d\n",mun%10);
		mun=mun/10;
	}
	

	return 0;
}