#include <stdio.h>
#include <string.h>



int main()
{ 
  int n;
  printf("请输入字符串中元素总个数\n");
  scanf("%d", &n);
  char A[n];
  char B[n];

  //先初始化
  memset(A, 0, n);
  memset(B, 0, n);

  printf("请输入一个字符串\n");
  scanf("%s", A);

  for (size_t i = 0; i < strlen(A); i++)
  {
    //第一步:循环求出各个位,然后左移动
    for (size_t j = 0; j < 8; j++)
    {
      B[i] |= ((A[i] >> (7 - j)) & 0x1) << j;
    }
  }

  for (size_t i = 0; i < strlen(B); i++)
  {
    printf("a每个字节逆序之后:%x\n", B[i]);

  }
}
