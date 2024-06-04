#include<stdio.h>

int main()
{
    //练习3：定义一个整型数组，存储从键盘上获取的多个整型数据（比如输入 10  40  23  13），并且打印出 这一排数据的最小值和最大值。
    int len=0;
    printf("请输入数据的个数:");
    scanf("%d",&len);

    //定义数组  ---变长数组 仅仅指元素个数在定义时是变量，而绝非指数组的长度可长可短。
    //变长数组 在定义的时候不能直接初始化
    int array[len];
    //清空数组
    //memset 第一个参数代表你要清空的内存空间的起始地址
    //第二个参数代表 你要往这片内存空间赋的值
    //第三个参数代表 这片内存空间多大  多少个字节
    memset(array,0,sizeof(array));

    for(int i=0; i<len; i++)
    {
        scanf("%d",&array[i]);
    }

    //比较获取最小值和最大值
    int min = array[0];
    int max = array[0];

    //遍历数组
    for(int i=1; i<len; i++)
    {
        if(min > array[i])
            min = array[i];
        
        if(max < array[i])
            max = array[i];
    }

    printf("min:%d max:%d\n",min,max);
}