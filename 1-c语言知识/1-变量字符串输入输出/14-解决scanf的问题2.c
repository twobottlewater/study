#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()  
{
	int a;
	char b;
	int ret;
	
	printf("请输入一个整数和一个字符!\n");
	scanf("%d",&a);
	
	//主动清除缓冲区里面残留的\n
	ret=getchar();
	printf("getchar从缓冲区里面读取的字符，ASCII码值是: %d\n",ret);
	
	scanf("%c",&b);
	
	//打印输入的结果
	printf("您刚才输入的数据是: %d   %c\n",a,b);
	return 0;
}