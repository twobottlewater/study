#include <stdio.h>
#include <string.h>

     int main()
     { 
      char buf[100]={0};
      char otherbuf[100]="我爱中国";

/*         strncpy(buf,"world",2);//把world最前面的两个字节拷贝到buf里面
        printf("%s\n",buf); */


      strncpy(buf,otherbuf,6 );//把world最前面的两个字节拷贝到buf里面
      printf("buf is %s\n",buf); 

     }