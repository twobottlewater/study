#include <stdio.h>
#include <string.h>

// 函数原型声明
int findSubstring(const char *str, const char *substr);

int main() {
    char str[] = "Hello, World!";
    char substr[] = "World";

    int position = findSubstring(str, substr);  // 调用自定义的字符串查找函数
    if (position >= 0) {
        printf("Substring '%s' found at position %d in '%s'\n", substr, position, str);
    } else {
        printf("Substring '%s' not found in '%s'\n", substr, str);
    }
    
    return 0;
}

// 函数定义
int findSubstring(const char *str, const char *substr) {
    if (!*substr) return 0; // 如果子字符串为空，则视为在位置0找到

    const char *p, *q, *start;
    for (start = str; *start; start++) { // 遍历每个可能的起始位置
        for (p = start, q = substr; *q && *p && *p == *q; p++, q++) {} // 比较子字符串
        if (!*q) // 如果成功匹配到子字符串的结束
            return start - str; // 返回子字符串的起始位置
    }
    return -1; // 未找到子字符串
}
