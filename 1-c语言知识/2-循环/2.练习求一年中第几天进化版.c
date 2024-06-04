#include <stdio.h>
 
int main()
 {
	int day,month,year;
	char i;
lb:
	printf("请输入日月年\n");
	scanf("%d%d%d",&year,&month,&day);

	if(month<=0||month>12)
	{
		printf("您输入的月份有误,只能是1--12月\n");
		goto lb;
	}
	else		//月份合法-->>进一步判断日期是不是合法的
	{
		if(month==4|| month==6 ||month==9|| month==11)
		{
			if(day>=1&&day<=30)
			{
				printf("日期合法\n");
			}
			else
			{
				printf("日期非法,1-30\n");	
				goto lb;
			}
		}
		
		else if(month==2)
		{
			if((year%4==0 && year%100!=0)||(year%400==0))//闰年
			{
				if(day>0 && day<30)
				{
					printf("日期合法\n");
				}
				else
				{
					printf("日期非法,1-29\n");
					goto lb;
				}
			}
			
			else
			{
				if(day>0 && day<29)
				{
					printf("日期合法\n");
				}
				else
				{
					printf("日期非法,1-28\n");
					goto lb;
				}
			}
		}
		else
		{
			if(day>=1 && day<=31)
			{
				printf("日期合法\n");
			}
			else
			{
				printf("日期非法,1-29\n");
				goto lb;
			}
		}
	}
	switch(month)
	{
		case 12:
			day+=30;
		case 11:
			day+=31;
		case 10:
			day+=30;
		case 9:
			day+=31;
		case 8:
			day+=31;
		case 7:
			day+=30;
		case 6:
			day+=31;
		case 5:
			day+=30;
		case 4:
			day+=31;
		case 3:
			day+=28;
		case 2:
			day+=31;
	}
	if((year%4==0&& year%100!=0)||(year%400==0))
	{
		if(month>2)
		day+=1;
	}
	printf("您输入是这年第%d天\n",day);
	while ( 1 )
	{
		/* code */
	}
	
  }
	
	
