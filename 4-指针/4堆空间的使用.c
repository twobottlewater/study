#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int *p=malloc(20);
    *p=66;
    printf("p is %d\n",*p);
}