#include <stdio.h>
#include <string.h>
// 函数定义
void reverseString(char *str)
{
    int i = 0;
    int j = strlen(str) - 1;
    while (i < j) {
        // 交换字符
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;

        i++;
        j--;
    }
}


int main() {
    char str1[] = "Hello, World!";
 

    reverseString(str1);
    // 比较两个不同的字符串
    printf("翻转之后的数据是%s\n", str1);

    return 0;
}

