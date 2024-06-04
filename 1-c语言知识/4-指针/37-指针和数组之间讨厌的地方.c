#include <stdio.h>
#include <string.h>

/*
指针和数组名之间讨人厌的地方和注意事项
*/
int main()
{ 
  int buf[1];
  sizeof(buf);  //错误的：死记，是指针，8个字节
  printf("大小is :%d\n",sizeof(buf));
  printf("大小is :%p\n",buf); 
}
