#include <stdio.h>
#include <string.h>


int main()
{
	int i,j,k;
	char A[100]={0};
	char B[100]={0};
	printf("请输入两个字符串\n");
	scanf("%s%s",A,B);
	
	//先遍历B里面的字符
	for(i=0;i<strlen(B);i++)
	{
		for(j=0;j<strlen(A);j++)
		{
			if(B[i]==A[j]|| B[i]-A[j]==32 || B[i]-A[j]==-32)
			{
				//把A中为i的原素删除
				for(k=j;k<strlen(A);k++)
				{
					A[k]=A[k+1];
					
				}
				j--;
			}
		}
	}
	
	printf("删除后A的内容是：%s\n",A);
	return 0;
}
