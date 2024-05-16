#include <stdio.h>
#include <string.h>

int main()
{
	int i,j;
	//定义变量保存字符串的最开始真实大小
	int size;
	char buf[20]={0};//惯例先清0

	printf("请输入一个字符串!\n");
	scanf("%s",buf);
	
	
	printf("请你输入要把hello插入到刚才那个字符串的下标i的前面,输入i的值.\n");
	scanf("%d",&i);
	// printf("buf的是%s\n",buf);
	
	//保存buf的原始长度大小
	size=strlen(buf);
	
	// printf("size的长度:%d\n",size);
	// printf("sizeof的长度:%d\n",sizeof(buf));//这个永远是20
	
	
	//判断i的合法性,buf的总长度够不够
	if((i>=0) && (i<size) && (sizeof(buf)-size>5))
	{
		//从下表i开始,往后挪动
		for(j=0;j<size-i;j++)
		{
			buf[size+4-j]=buf[size-1-j];
		}
	}
	else
	{
		printf("输入不合法或者下标不够\n");
		return -1;
	}
	
	buf[i]='h';
	buf[i+1]='e';
	buf[i+2]='l';
	buf[i+3]='l';
	buf[i+4]='o';
	//打印结果
	printf("现在结果是:%s\n",buf);
	
}