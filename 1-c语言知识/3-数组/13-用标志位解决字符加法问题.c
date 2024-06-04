#include <stdio.h>
#include <string.h>
#include <strings.h>
int main()
{
	int i,j=0;
	int n1,n2; //保存每一位数
	int temp;
	int flag=0;//标志位
	
	char num1[100]={0};
	char num2[100]={0};
	char result[100]={0}; //存放结果
	printf("请输入两个很大的整数！\n");
	scanf("%s%s",num1,num2);
	
	//求出两个字符串实际长度
	int size1=strlen(num1);
	int size2=strlen(num2);
	
	//求出两个字符串长度较小的
	int min=size1>size2?size2:size1;
	int max=size1<size2?size2:size1;
	//计算结果
	for(i=0;i<min;i++)
	{
		//把字符转换成整数
		n1=num1[size1-1-i]-'0';
		n2=num2[size2-1-i]-'0';
		if(n1+n2+flag>=10)//往高进位
		{
			temp=n1+n2+flag-10;
			result[j]=temp+'0';		
			flag=1;
		}
		else //不需要往高进位
		{
			temp=n1+n2+flag;
			result[j]=temp+'0';	
			flag=0;
		}
		j++;
	}
	for(; i<max; i++)
	{
		if(size1>size2)
			n1=num1[size1-1-i]-'0';
		else
			n1=0;
		if(size2>size1)
			n2=num2[size2-1-i]-'0';
		else
			n2=0;
		if(n1+n2+flag>=10)//往高进位
		{
			temp=n1+n2+flag-10;
			result[j]=temp+'0';		
			flag=1;
		}
		else 
		{
			temp=n1+n2+flag;
			result[j]=temp+'0';	
			flag=0;
		}
		j++;
	}
	if(flag)
	{
		result[j]='1';
		j++;
	}
	result[j]='\0';
	//反转结果
	for(i=0; i<j/2; i++)
	{
		char t=result[i];
		result[i]=result[j-1-i];
		result[j-1-i]=t;
	}
	printf("结果是:%s",result);
	return 0;
}
