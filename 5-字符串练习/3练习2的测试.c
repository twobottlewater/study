#include <stdio.h>
#include <string.h>


 //20.输入两个正整数A和B，计算这两个数相比较有多少个二进制位不同
int main()
{ 


    unsigned int num;
    printf("请输入一个正整数：\n");
    scanf("%u", &num);
    int i = 0;
    char buf[32];
    while (num > 0 && i < 32) {
        buf[i++] = num % 2 ;
        num /= 2;
    }

    for (size_t i = 0; i < 32; i++)
    {
        printf("%d",buf[i]);
    }
    
    // printf("该正整数的二进制数为：%s\n", buf);
    return 0;


}
