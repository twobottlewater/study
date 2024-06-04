#include <stdio.h>
#include <string.h>

     int main()
     { 
   
      int ret;
      char buf[100]="hello ";
      char otherbuf[100]="world";

      //buf和other合并一起存在buf中
     strcat(buf,otherbuf);
     
        printf("%s\n",buf);
     
     
    
      return 0;
     }