#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DBG_PRINTF(fmt,args...)\
{\
    printf("<<File:%s\t Line:%d \t Function:%s>> ",__FILE__, __LINE__, __FUNCTION__);\
    printf(fmt,##args);\
} //宏定义一行写不下要用续行符连接，args后面加...就是用来省略参数的类型和个数
 
static void test1(void)
{
    int a=1,b=2;
    DBG_PRINTF("a+b=%d\n",(a+b));
}
static void test2(void)
{
    DBG_PRINTF("hello world!!!\n");
}
static void test3(void)
{
    int a=1,b=2,c=0;
    DBG_PRINTF("%d %d\n",c=a+b,a=c+b);
}
int main(void)
{
    test1();
    test2();
    test3();
    return 0;
}