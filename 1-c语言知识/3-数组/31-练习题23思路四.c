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
    char label[10] = {0}; // 记录出现过的数字
    for (int i = 0; i < 10; i++)
    {
        if (label[arr[i]] == 0)
            label[arr[i]] = 1;
    }
    // 找出缺失的数
    for (int i = 0; i < (sizeof(label) / sizeof(char)); i++)
    {
        if (label[i] == 0)
            printf("缺失数据为%d\n", i);
    }
}
