#include <stdio.h>
#include <string.h>


int main()
{
	char a[10];
    printf("请输入一个字符串\n");
    scanf("%s",a);

    int len=strlen(a);
    for (int i = len-1; i >=0; i--)
    {
         printf("%c",a[i]);
    }

}