#include <stdio.h>
#include <string.h>
#include <strings.h>
int main()
{
	int i,j;
	int a[5][6]={{5},{8,9},{89,63}};  //正确,分组初始化 
		
	for(i=0;i<5;i++)
	{
		for(j=0;j<6;j++)
		{
			printf("a[%d][%d]的结果是：%d\n",i,j,a[i][j]);
		}
	
	}
	return 0;
}