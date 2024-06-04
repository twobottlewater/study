#include<stdio.h>

int main()
{
    int arr[5] = {10,20,30,40,50};

    printf("arr addr:%p\n",arr);
    printf("arr+1 addr:%p\n",arr+1);
    printf("&arr addr:%p\n",&arr);
    printf("&arr+1 addr:%p\n",&arr+1);

    //获取到数据20的方法
    printf("%d\n",arr[1]);

    //*(arr+1) = 100;

    printf("%d\n",*(arr+1));

    //获取数据10的方法
    printf("%d\n",arr[0]);
    printf("%d\n",0[arr]);
    printf("%d\n",*arr);
    printf("%d\n",*(arr+0));

    //14
    char str[] = "www.baidu.com";
    printf("%d\n",(unsigned int)(&str+1) - (unsigned int)&str);

	return 0;
}