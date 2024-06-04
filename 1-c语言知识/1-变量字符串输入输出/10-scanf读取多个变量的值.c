#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()  
{
	int a;
	float b;
	double c;
	printf("请输入一个整数，两个小数!\n");
	//scanf("%d",&a);
	//printf("a的值: %d\n",a);
	//scanf("%f",&b);
	//scanf("%lf",&c);
	
	scanf("%d%f%lf",&a,&b,&c);
	printf("a is: %d\n",a);
	printf("b is: %f\n",b);
	printf("c is: %lf\n",c);
	
}