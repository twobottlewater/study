#include <stdio.h>

int main()
{
	int i,j;
	int a[2][3];
	
	for(i=0; i<2; i++) //行
	{
		for(j=0; j<3; j++) //列
			scanf("%d",&a[i][j]);  
	}
//打印元素值
	for(i=0; i<2; i++) //行
	{
		for(j=0; j<3; j++) //列
			printf("a[%d][%d] is: %d\n",i,j,a[i][j]);
	}
	return 0;
}