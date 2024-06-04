#include<stdio.h>
/*
练习7： 判断输入的单个字符，如果是字符a到z  或者  A到Z ，则打印yes  
否则打印no。如果输入'#' ，退出程序
*/
int main()
{
    while(1)
    {
        char ch;
        printf("请输入单个字符:");
        scanf("%c",&ch);   //a\n 

        //去掉换行符
        getchar();

        if(ch == '#')
            break;

        if((ch >='a' && ch<='z')  ||   (ch>='A' && ch<='Z'))
        {
            printf("yes\n");
        }
        else 
            printf("no\n");

    }
}