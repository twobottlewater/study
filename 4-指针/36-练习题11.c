#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

void main()
 {
    char *s[]={"one","two","three"},*p;  //s是指针数组
    p=s[1];
    printf("%c,%s\n",*(p+1),s[0]);  //w   "one" 
 }