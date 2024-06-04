#include <stdio.h>
#include <string.h>


 //20.输入两个正整数A和B，计算这两个数相比较有多少个二进制位不同
int main()
{ 
  int A,B;
  int count=0;
  int i=0;
  int buf1[32]={0};
  int buf2[32]={0};
  printf("请输入两个正整数\n");
  scanf("%d%d",&A,&B);
  while (1)
  {
    buf1[i++]=A%2;
    A=A/2;
    if (A==0)
    {
      break;
    }
  }

  i=0;
  
  while (1)
  {
    buf2[i++]=B%2;
    B=B/2;
      if (B==0)
    {
      break;
    }
  }
  for (size_t i = 0; i < 32; i++)
  {
    if (buf1[i]!=buf2[i])
    {
      count++;
      printf("从低位到高位开始第%d位二级制是不同的\n",i);
      /* code */
    }
  }
  printf("a和b总共有%d个二进制不同\n",count);
}
