#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()  
{
	int a,b,c;
	//定义变量保存scanf的返回值
	int ret;
	
	printf("请输入三个整数!\n");
	ret=scanf("%d%d%d",&a,&b,&c);
	printf("scanf的返回值是: %d\n",ret);
	
	return 0;
}