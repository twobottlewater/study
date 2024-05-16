#include <stdio.h>

/*
	C语言编程技巧==》使用标志位(开关位)
	int flag=0;
	
	if(条件)
	{
		flag=1;
	}
	
	if(flag==1)
	{
		
	}
	else
	{
		
	}
*/
int main()
{
	int num;
	int i;
	int digital; //保存你计算得到的某个位
	//C语言编程技巧==》使用标志位
	int flag=0;
	//C语言编程技巧==》定义临时变量，保护现场
	int temp;
	
	printf("请输入0---100000范围以内的某个数!\n");
	scanf("%d",&num);
	//判断一下num是否符合要求
	if(!(num>=0 && num<=100000))
	{
		printf("对不起，您输入的数据不符合要求!\n");
		return -1;
	}
	
	//判断数字能否被6整除，或者数字当中是否含有6
	for(i=0; i<=num; i++)
	{
		//判断i能否被6整除
		if(i%6==0)
			printf("%d可以被6整除!\n",i);
		else //i不可以被6整除
		{
			//把当前i的值存放到临时变量temp里面
			temp=i; //57
			//进一步判断，该数字中是否含有6
			//把i的各个位求出来
			while(temp!=0)
			{
				digital=temp%10; //求出某个位
				if(digital==6) //说明该数字中含有6
				{
					flag=1;
				}
				temp=temp/10;
			}
			//装模作样判断flag的值
			if(flag==1) //说明在while中flag被改变了--》说明数字中含有6
			{
				printf("恭喜，%d 该数字中含有6\n",i);
				flag=0; //标志位使用完毕，记得重新归零
			}
				
		}
	}
		
}
	
	
