#include<stdio.h>
#include <stdbool.h>
#include <string.h>

int main()
{
    //passwd数组内存是6个字节   但是有效的字符串长度是5，所谓的有效 就是不包括\0
    char passwd[ ] = "123rr";

    printf("%d\n",strlen(passwd));
    printf("%d\n",sizeof(passwd));


    //有同学会这么做
    int arr[6];
    //错误的，因为 arr是整形数组，strlen是用于测量字符串的长度
    //printf("%d\n",strlen(arr));
}