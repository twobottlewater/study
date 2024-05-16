#include <stdio.h>
#include <string.h>

int main()
{
	int i;
	char buf[20];
	
	while(1)
	{
		printf("请输入一个字符串\n");
		scanf("%s",buf);
		//printf("你刚刚输入的字符串是%s\n",buf);
		for(i=0;i<20;i++)
			printf("数组buf[%d]存放的字符是:%c  ASCII码是:%d\n",i,buf[i],buf[i]);
	}
	
}