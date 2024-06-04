#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()  
{
	int a;
	int ret;
     printf("请输入一个整数:\n");
     ret=scanf("%d",&a);
     if (ret==1)
     {
           printf("你刚刚输入的整数是:%d\n",a);
     }
     else
     {
            printf("你刚刚输入的就不是整数\n");

     }
    
	
}