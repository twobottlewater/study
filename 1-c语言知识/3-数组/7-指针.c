#include<stdio.h>
#include <stdbool.h>
#include <string.h>

int main()
{
    // int a = 10;

    // printf("a addr:%p\n",&a);


    // int *p = &a;

    // printf("p的值 %p\n",p);
    
    //对指针变量进行解引用 就是 取 指针变量所指向内存空间的数据
    // *p ==> *（&a） ==>  a
    // *p = 120;
    // printf("a :%d\n",a);


    int arr[5] = {10,20,30,40,50};
    int (*p) = arr;

    printf("%d %d\n",*(p+4),p[4]);

     int (*pt)[5] = &arr;  

     printf("%d\n",*(*pt+2));


    //遍历数组
    for(int i=0; i<5; i++)
    {
        printf("%d\t",arr[i]);
    }
}