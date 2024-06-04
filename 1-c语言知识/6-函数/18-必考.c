#include<stdio.h>
/*
void fun(char *(*p))
{
    ++p;
    printf("%s\n",*p);
}

int main() {
   char *a[]={"MORNING","AFERNOON","EVENING","NIGHT"};
  fun(a);   
}

*/
#include <stdio.h>
#include <string.h>

char *getmemory(void) {
  char *p []= "hello"; // 字符串字面量是一个静态分配的字符数组
  return p;
}

int main(void) {
  char *p;
  p = getmemory();
  printf("%s\n", p);
  return 0;
}
