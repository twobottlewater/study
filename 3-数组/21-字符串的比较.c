#include <stdio.h>
#include <string.h>

     int main()
     { 
   
      int ret;
      char buf[100]="fhcsfhdhfh";
      char otherbuf[100]="zbc";

      //比较什么字母排在前面而已
      ret=strcmp(buf,otherbuf);
      if (ret>0)
      {
        printf("buf>otherbuf\n");
      }
      else
        printf("buf<otherbuf\n");
    
      return 0;
     }