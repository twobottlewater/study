#include <stdio.h>
#include <string.h>
#include <stdlib.h>

 char *GetMemory1()
     {
        char p[]="hello world";
        return p;
     }
void GetMemory2(char *p)
     {
        p=(char *)malloc(100);
     }
int main()
{
   char *str1=NULL,*str2=NULL;
        //str1=GetMemory1();
        //str1=p;
        //printf("%s\n",str1);
        GetMemory2(str2);
        strcpy(str2,"hello world");
        printf("%s\n",str2);

}