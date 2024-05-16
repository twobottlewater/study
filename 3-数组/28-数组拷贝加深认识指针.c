#include <stdio.h>
#include <string.h>
 int main()
 { 
   //任务我就是要吧other buf的wo拷贝到hello里面
    char buf[20]={0};
    char otherbuf[20]="helloworld";
   strncpy(buf,otherbuf+5,2);
   printf("%s\n",buf);
  

    return 0;
     }
