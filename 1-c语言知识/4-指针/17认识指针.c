#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
	int a=11;
    int *p;   
    p=&a; 
    printf("*p is: %p\n",*p); 
    /*  *p里面存的就是a的值啊   p存的是a的地址  */  
    printf("p is: %p\n",p);  
    printf("&a is: %p\n",&a);  
    printf("指针p地址中存放的数据是: %d\n",*p);
  
}