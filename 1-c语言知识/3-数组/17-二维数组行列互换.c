#include <stdio.h>
 

int main()
{
	
	
	int i,j;
	int temp;
	int a[5][5];
	int n=1;

	/* for(i=0;i<5;i++)
	{
		j=0;
	  	printf("ai%d行是%d %d %d %d %d\n",i,a[i][j],a[i][j+1],a[i][j+2],a[i][j+3],a[i][j+4]);
	} */
	//高级赋值方法
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
			a[i][j]=n++;
	}
	
	//打印初始结果
	printf("打印初始结构\n");
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		printf("%-4d",a[i][j]);
		printf("\n");
		}
	//行列互换	
	for(i=0;i<5;i++)
	{
		//printf("i is %d\n",i);
		for(j=i;j<5;j++)
		{
			//printf("i is %d\n",i);
			// printf("j is %d\n",j);
			temp=a[i][j];
			a[i][j]=a[j][i];
			a[j][i]=temp;
			}
		}
	//打印z最终结果
	printf("打印最终结构\n");
		
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		printf("%-4d",a[i][j]);
		printf("\n");
		}
	

	
	// for(i=0; i<2; i++) //行
	// {
	// printf("存放的字符串是%s\n",a[i]);
	// } 
	
	return 0;
}