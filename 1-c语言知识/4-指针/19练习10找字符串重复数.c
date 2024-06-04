#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
/*
编程找到任意一个字符串中哪个字符连续重复出现的次数最多，
找到之后打印这个字符以及它连续重复出现的次数。例如，若为"aaabbbb",
打印连续出现次数最多的字符是b，个数是4 ；若字符串为  "abcde"，
(abcde都只出现了一次，打印排在前面的那个)，打印a出现1次
*/

int main()
{
	int i,j;
	//定义变量保存最终连续的重复的次数最多的字符
	int max=0;
	int max_index=0;
	int n=1;
	char buf[50]={0};
	char mbuf[2]={0};
	int temp;
	printf("请输入任意一个字符串\n");
	scanf("%s",buf);
	
	for(i=0;i<strlen(buf);i++)
	{
	  n=1;//回归初始值
		for(j=i+1;j<strlen(buf);j++)
		{
			if(buf[i]==buf[j])//连续重复
			{
			 n++;
			}
			else
			{
			 break;
			}
		}
			if(max<n)//更新max的值
			{
			 max=n;
			 max_index=i;
			}
	}
	printf("连续重复次数最多的是:%d\n",max);
	printf("出现最多的字符是%c\n",buf[max_index]);
	return 0;
}