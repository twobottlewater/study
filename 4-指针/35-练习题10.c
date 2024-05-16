#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
/*
	指针如果要跟数组写法一模一样，前提条件是该指针类型必须跟数组名代表的指针类型一致
*/
int main()
{
	char  b[5][10]={"hello", "world", "gechehe","china"}; 
      *(b[1]+2)='c';  //c替换world中的r 
      char (*p)[10]=&b[2];
      p++; //&b[3]
      printf("p is:%s\n",*p);//等价替换*&b[3]-->b[3]
      printf("b[1]  is:%s\n",b[1]);  //"wocld"
}