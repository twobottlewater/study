#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
/*
	指针如果要跟数组写法一模一样，前提条件是该指针类型必须跟数组名代表的指针类型一致
*/
int main()
{
	char  buf[5][10]={"hello","world","china"};
    char *p=&buf[1][3];  
    char *q=&buf[2][1]; 
    printf("q-p  is:%d\n",q-p); //间隔了多少个元素
}