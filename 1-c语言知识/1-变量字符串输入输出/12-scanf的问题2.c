#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()  
{
	int a;
	char b;
	printf("请输入一个整数和一个字符!\n");
	scanf("%d",&a);
    	getchar();
	//你刚才输入完整数以后，会敲个回车，回车会被当成字符读取
	scanf("%c",&b);
	
	//打印输入的结果
	printf("您刚才输入的数据是: %d   %c\n",a,b);
	return 0;
}
