#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
     {
         char *p="abcdefgh",*r;
         int *q;
         q=(int *)p;
         q++; //q=q+1;  q是int类型，加1，加4个字节
         r=(char *)q;
         printf("r is :%s\n",r);  //%s从指定的起始位置开始，遇到\0结束打印  efgh
        

        return 0;
     }
