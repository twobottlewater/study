#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

/*
9.写一个程序处理字符串A，处理规则是: 只要字符串B里面有的字符，不论大小写，一律从A字符串中删除  
*/

int main()
{
    char *p;
    char A[100]={0};
    char B[100]={0};

    printf("q请输入两个字符串\n");
    scanf("%s%s",A,B);
    int len1=strlen(A);
    int len2=strlen(B);
    
    if ((p=strstr(B,A))!=NULL)
    {
        /* code */
        strncpy(p,p+strlen(A),strlen(p+strlen(A))+1);
        bzero(B+(len2-len1)+1,len1);
    }
    else
    {
        printf("A在B中不存在\n");
        return 1;
    }
    //验证答案
    printf("删除A之后,B里面是%s\n",B);
    for (size_t i = 0; i < 20; i++)
    {
       printf("%c ascii 码值是：%d\n",B[i],B[i]);
    }
    

    return 0;
}