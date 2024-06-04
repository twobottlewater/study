#include <stdio.h>

int main() {
    int number, digit, position = 1;

    printf("请输入一个整数: ");
    scanf("%d", &number);

    printf("整数的每一位大小如下：\n");

    while (number > 0) {
        digit = number % 10;  // 取末尾数字
        printf("第%d位是%d\n", position, digit);
        number /= 10;  // 去掉末尾数字
        position++;
    }

    return 0;
}