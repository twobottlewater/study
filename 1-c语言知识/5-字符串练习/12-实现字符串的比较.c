#include <stdio.h>

// 函数原型声明
int myStrcmp(const char *s1, const char *s2);

int main() {
    char str1[] = "Hello, World!";
    char str2[] = "Hello, World!";
    char str3[] = "Hello, OpenAI!";

    // 比较两个相同的字符串
    printf("Comparing '%s' to '%s': %d\n", str1, str2, myStrcmp(str1, str2));

    // 比较两个不同的字符串
    printf("Comparing '%s' to '%s': %d\n", str1, str3, myStrcmp(str1, str3));

    return 0;
}

// 函数定义
int myStrcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return (*s1 == *s2) ? 0 : 1;  // 如果两字符串结束符同时到达，则相等；否则，不等
}
