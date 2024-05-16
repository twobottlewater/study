#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    double a=89;
    double b=96;
    double *p1=&a;
    double *p2=&b;
    printf("p1 is :%p\n",p1);
    printf("p2 is :%p\n",p2);
    printf("p2-p1 is :%ld\n",p2-p1);
     return 0;
}

