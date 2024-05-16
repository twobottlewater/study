#include <stdio.h>
#include <math.h>
int main()
{
	int i;
	int a;
	int n;/*	表示多少项 */
	int	temp;//中间变量保存结果
	int result;
	
	printf("请输入求的底\n");
	scanf("%d",&a);
	printf("请输入求项数\n");
	scanf("%d",&n);
	result=a;
	temp=a;
	
	for(i=0;i<n-1;i++)
	{
		temp=temp+a*pow(10,i+1);  //temp   3+3*10+3*100   相当于每次进来都加了个300或者30
		
		result=result+temp;	 // result 	3+3+3*10+3+3*10+3*100
							//等于     3 +33     +333
		
	}
	
	//打印结果
	printf("结果是:%d\n",result);
	
	
}