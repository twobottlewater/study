#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
     {
        char ss2[]="abcde";
        int r;
        r=strlen(ss2);//字符串的实际长度
        int t;
        t=sizeof(ss2);//64位系统就是8字节
        printf("%d\n",r);
        printf("%d\n",t);
        

        return 0;
     }
