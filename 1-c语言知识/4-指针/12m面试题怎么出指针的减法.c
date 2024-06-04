#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
double a=89;  
double *p=&a;    
printf("p is: %p\n",p);   
printf("p-1 is: %p\n",p-1);
}

//注意加减的1是类型大小的1就可以了