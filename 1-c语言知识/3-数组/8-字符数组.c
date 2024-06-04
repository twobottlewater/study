#include<stdio.h>

// 递归函数用于转换十进制数为二进制
void decimalToBinary(int n, int *count) {
    if (n == 0) {
        return; // 递归结束条件
    } else {
        decimalToBinary(n / 2, count); // 递归调用，除以2
        (*count)++;
        if (*count % 4 == 0) {
            printf(" "); // 每4个二进制数后打印一个空格
        }
        printf("%d", n % 2); // 打印余数
    }
}

int main()
{
    int decimalNumber;
     int count = 0;
    printf("Enter a decimal number: ");
    scanf("%d", &decimalNumber);

    printf("Binary representation: ");
    decimalToBinary(decimalNumber,&count); // 调用递归函数
    printf("\n");
}