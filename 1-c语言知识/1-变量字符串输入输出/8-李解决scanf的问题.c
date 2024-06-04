#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()  
{
	int a;
	int ret;
    int n;
     printf("请输入一个整数:\n");
     ret=scanf("%d",&a);
    //判断用户输入是不是输入了整数
     if (ret==1)
     {
            //进一步进行判断
            //立马从缓冲区读取一个数
            n=getchar();
            if (n!='\n')
            {
               printf("对不起你输入不对思密达\n");
            }
            else  
            {
              printf("你刚刚输入的整数是:%d\n",a);
            }
     }
     else
     {
            printf("你刚刚输入的就不是整数\n");

     }
    
	
}