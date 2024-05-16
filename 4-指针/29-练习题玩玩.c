#include <stdio.h>
#include <string.h>

 void  main( )
{  
        /*char  s[]="Hello World!";
        char* p = s;
        int n=10;
        printf("%d %d %d %d\n",sizeof(s),sizeof(p),strlen(p),sizeof(n));  //13  8  12  4

        这个是第七题
        */
       /*这个是第八题*/
     char  buf[10]="gecchina";
     char *p=&buf[3];
     p=p+2;
     *p='#';
     printf("buf is:%s\n",buf);  //gecch#na
     printf("p is:%s\n",p); //#na
    
}                           