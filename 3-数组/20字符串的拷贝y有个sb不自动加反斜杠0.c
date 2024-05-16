#include <stdio.h>
#include <string.h>

     int main()
     { 
      char buf[100]="helloworld";
      char otherbuf[20]="uuu";

/*         strncpy(buf,"world",2);//把world最前面的两个字节拷贝到buf里面
        printf("%s\n",buf); */


      strcpy(buf,otherbuf);//把world最前面的两个字节拷贝到buf里面
      printf("buf is %s\n",buf); 
      return 0;
     }