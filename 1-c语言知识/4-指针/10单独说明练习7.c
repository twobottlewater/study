#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
   char *str2=NULL;
    char *p=str2;//两个指针都指向空null
    printf("p is %p\n",p);
    printf("str2 is %p\n",str2);
    p=malloc(100);
    printf("移情别恋后p is %p\n",p);
    printf("str2 is %p\n",str2);

    strcpy(str2,"hello world");
   printf("%s\n",str2);

}