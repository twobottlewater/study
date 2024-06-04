#include<stdio.h>
#include <stdbool.h>
#include <string.h>
int main()
{
    /*
    2、现在有两个字符数组
char  str1[10] = {0};
char  str2[10] = "hellozou";
请将str2数组里面的内容拷贝到str1中

    */
    char  str1[10] = {0};
    char  str2[10] = "hellozou";

    //遍历str2数组 ，一个字符一个字符地赋值
    // int j=0;
    // while(1)
    // {
    //     //*(str2+j)   ==>  str2[j]
    //     if(*(str2+j) == '\0')
    //         break;

    //     //赋值
    //     str1[j] = str2[j];

    //     j++;
    // }
    strcpy(str1,str2);

    printf("str1:%s\n",str1);

	return 0;
}