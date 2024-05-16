#include <stdio.h>

int main()
{
  unsigned int x = 0x12345678;
  char *p = (char *)&x;

  if (p[0] == 0x78) {
    printf("小端存储\n");
  } else {
    printf("大端存储\n");
  }

  for (size_t i = 0; i < 4; i++)
  {
    printf("%x\n",(*p++));
    /* code */
  }
  

  return 0;
}