#include <stdio.h>
#include <string.h>
/*
      23.已知一个数组中随机存放着0到n这些数字(杂乱无序的),
      某人从其中删除了一个数字，请你编程实现判断删除的是哪个数字
      */
   
int main()
{
    // 定义一个杂乱无章的数组存放数组
    int arr[10] = {3, 1, 9, 8, 0, 6, 5, 4, 7};
    int sum=0;
    
    for (int i = 0; i < 10; i++)
    {
        sum=sum^arr[i]^i;
    }
   
    printf("缺失的是:%d\n",sum);
    return 0;

}
