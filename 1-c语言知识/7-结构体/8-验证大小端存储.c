#include <stdio.h>

/*
union
{
    int i;
    char x[2];
}a;
int main()
{
    a.x[0]=10;
    a.x[1]=1;       //打印的实现从高位数下来    就是0000   0001   0000 1010
    printf("%d",a.i); //结果是多少?  266  
}*/
int main()
{
	short big = 0xff00;
	char litter = big;
	if (litter == 0xff)
	{
		printf("大");
	}
	else
	{
		printf("小");
	}
    return 0;
}