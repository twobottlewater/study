#include <stdio.h>
#include <string.h>
 
int main()
 {
	int i,j;
	char buf[20]={0};//清空
	char delchar;//要删除的字符
	
	printf("请输入任意一个字符!\n");
	scanf("%s",buf);
	
	//清除缓冲区残留的\n	
	getchar();
	
	printf("请输入你要删除的字符\n");
	scanf("%c",&delchar);
	//printf("读取的字符是:%d\n",delchar);
	
	for(i=0;i<strlen(buf);i++)
	{
		//判断当前字符是不是要删除的
		if(buf[i]==delchar)
		{
			/*
			buf[i]=buf[i+1]
			buf[i+1]=buf[i+2]
			buf[i+2]=buf[i+3]
			*/
			for(j=i;j<strlen(buf);j++)
			{
				buf[j]=buf[j+1];
			}
			//很重要，防止漏掉连续挨在一起的重复字符
			i--;
			//相当于删除了一个元素全部前移了,然后我再从那个位置检查起来
			
		}
	
	}
	//打印结果
	printf("删除之后的结果是:%s\n",buf);
  }
	
	
