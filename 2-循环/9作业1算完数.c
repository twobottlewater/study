#include <stdio.h>
 
int main()
 {
	int i;
	int j;
	int sum=0;
	for(i=1;i<=8888;i++)
	{
		//求出i所有的公因子  i除以1到i-1
		for(j=1;j<=i-1;j++)
		{
			if(i%j==0)
			{
				//把这些公因子全部加起来
				sum+=j;
			}
		}
		
		//判断这些公营子和i是不是相等
		if(sum==i)
		{
			printf("恭喜找到一个完数:%d\n",i);
		
		}
			sum=0;
	}
  
  }
	
	
