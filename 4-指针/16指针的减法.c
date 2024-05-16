#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
	 int a=89;  
    int *p=&a;    
    printf("p is: %p\n",p);   
    printf("p-1 is: %p\n",p-1);

    printf("p地址里面的东西 is: %d\n",*p);   
    printf("p地址里面的东西减去1 is: %d\n",*p-1);
}