#include <stdio.h>
#include <string.h>

inline int fun(int a, int b)
{
 return a>b?a:b;
}

int main()
{ 
  int a=89;
  int b=56;
  printf("a和b比较大的是 %d\n",fun(a,b));
}
