#include <stdio.h>
#include <string.h>

/**/
/*
    //第一步:循环求出各个位,然后左移动
    for (size_t i = 0; i <4; i++)
    {
        result=result|((a&0x1<<i)<<(7-2*i));

    }
        for (size_t i = 0; i <4; i++)
    {
        result=result|((a&0x1<<(i+4))>>(2*i+1));

    }
    printf("结果是: %x\n",result); //b9-->> 1011 1001
                                  //        1001 1101
 */

int main()
{ 
  int n;
  printf("请输入字符串中元素总个数\n");
  scanf("%d",&n);
  char A[n];
  char B[n];

  //先初始化
  bzero(A,n);
  bzero(B,n);
  //b保存中间变量
  int result=0;
  printf("请输入一个字符串\n");
  scanf("%s",A);


  for (size_t j = 0; j <strlen(A); j++)
  {
    //第一步:循环求出各个位,然后左移动
    for (size_t i = 0; i <4; i++)
    {
      result=result|((A[j]&0x1<<i)<<(7-2*i));

    }
      for (size_t i = 0; i <4; i++)
    {
      result=result|((A[j]&0x1<<(i+4))>>(2*i+1));

    }
    //把结果放到b中
    B[j]=result;
    result=0;
  }
  for (size_t i = 0; i < strlen(B); i++)
  {
    printf("a每个字节逆序之后:%x\n",B[i]);
  }
  
}
