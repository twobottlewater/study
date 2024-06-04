#include <stdio.h>
void fun(char *(*p))  //char **p;
{
    ++p;   
    printf("%s\n",*p);
}
int main()
{
    char m='a';
    char *p=&m;
    char **q=&p;
    printf("q存放的地址：%p\n",q);
    printf("q+1存放的地址：%p\n",q+1);
    char *a[]={"morning","afternoon","evening","night"};  //指针数组
    fun(a);  
}