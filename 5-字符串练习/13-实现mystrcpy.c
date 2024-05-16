#include <stdio.h>

// 函数原型声明
void myStrcpy(char *dest, const char *src);

int main() {
    char src[50] = {0};
    printf("Enter a string: ");
    scanf("%s", src);
    char dest[50];  // 确保目标数组足够大以容纳源字符串

    myStrcpy(dest, src);  // 调用自定义的字符串复制函数

    printf("Copied string: %s\n", dest);  // 显示复制后的字符串
    return 0;
}

// 函数定义
void myStrcpy(char *dest, const char *src) {
    while (*src != '\0') {  // 检查源字符串的结束符
        *dest = *src;       // 复制当前字符
        dest++;             // 移动目标指针
        src++;              // 移动源指针
    }
    *dest = '\0';           // 在目标字符串末尾添加结束符
}
