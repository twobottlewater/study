#include <stdio.h>
#include <string.h>

int fun(int n)
{
  if (n==1)
  {
    return 1;
    /* code */
  }
  else
  {
    return n*fun(n-1);
  }
}

int main()
{ 
  printf("5的阶乘是:%d\n",fun(5));
}
