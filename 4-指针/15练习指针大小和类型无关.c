#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
	     int a,k,m;
         k=m=4;
         int *p1=&k,*p2=&m;
         a=p1==p2;
         printf("%d\n",a);
}