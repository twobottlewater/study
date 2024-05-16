#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

/*
这个代码接受两个字符串作为输入，第一个字符串为 A，第二个字符串为 B。
然后，它使用 strstr() 函数查找字符串 B 中是否包含字符串 A。
如果包含，则将字符串 A 从字符串 B 中删除。
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