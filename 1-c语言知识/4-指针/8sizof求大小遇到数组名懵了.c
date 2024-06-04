#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
     {
        int buf[20];
        int *p=buf;
        printf("sizof(p) is :%ld\n",sizeof(p));
        printf("sizof(buf) is :%ld\n",sizeof(buf));
        return 0;
     }
