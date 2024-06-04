#include<stdio.h>

int main()
{
    //需求：定义变量，存储10个同学的年龄
    //int a,b,c,d,e,f,g,h,l;
    //数组：将多个相同数据类型的元素 使用一个集合去表示
    //定义的时候初始化
    //如果后面初始化的值 小于 元素的个数，没有初始化的默认就是0
    //int array[10] = {11,22,33,44,55,66,77};
    //定义的时候清空数组
    //int array[10] = {0};
    //如果定义的时候已经确定好初始值了，那么[]里面的元素个数可以不写
    int array[ ] = {11,22,33,44,55,66,77,88,99,00};
    
    //测量某个变量/数据类型 占的字节  sizeof(array)

    //测量数组的长度 也就是说元素的个数 ？？？？
    //元素的个数 =  总的字节 / 每个元素 占的字节 
    int len = sizeof(array) / sizeof(array[0]);

    printf("len:%d\n",len);

    //元素的访问？？？ 通过数组下标索引去访问 0  1  2 
    array[0] = 11;
    array[1] = 22;
    //...
    array[9] = 99;

    for(int i=0; i<10; i++)
    {
        printf("[%d] value:%d addr:%p\n",i,array[i],&array[i]);
    }

    //如果这样写 是错误的  内存访问越界了
    //array[10] = 110;

}