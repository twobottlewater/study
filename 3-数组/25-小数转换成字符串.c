#include <stdio.h>
#include <string.h>

    // 11.将浮点数转换成字符串的思路: 先将浮点数强转取整，分别对整数部分和小数部分处理(小数部分不断*10，取整)

 int main()
 { 
    float a;
    int num=0;//统计整数的位数
    char buf[32]={0};
    int i=0;

    printf("请输入一个字符串\n");
    scanf("%f",&a);
    int n=(int)a;
    int temp=n;
    while (temp!=0)
    {
        temp%10;
        temp/=10;
        num++;//统计整数部分的位数
    }
    temp=n;
      while (temp!=0)//倒过来存
    {
        buf[num-1-i]=temp%10+'0';
        i++;
        temp/=10;
    }
    //存放小数点
    buf[i]='.';
    //printf("目前的结果是：%s\n",buf);      
    float pointnum=a-n;
    for (size_t j = 0; j < 10; j++)
    {
        pointnum*=10;
        buf[i+1]=(int)pointnum+'0';
        pointnum=pointnum-(int)pointnum;
        i++;
    }
    printf("目前的结果是：%s\n",buf);
    
    
	
    return 0;
     }
