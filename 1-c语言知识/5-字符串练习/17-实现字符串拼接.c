#include <stdio.h>

void myStrcat(char *dest, const char *src);

int main() {
    char dest[100] = "Hello, ";  // 确保 dest 数组足够大以容纳连接后的字符串
    char src[] = "World!";
    char str[100]="gecgecgec";
    myStrcat(dest, src);  // 调用自定义的字符串连接函数
    myStrcat(dest, str); 
    printf("Concatenated string: %s\n", dest);  // 显示连接后的字符串
    return 0;
}

// 函数定义
void myStrcat(char *dest, const char *src) {
    while (*dest) {  // 找到 dest 的末尾
        dest++;
    }
    while (*src) {  // 将 src 复制到 dest 的末尾
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';  // 在新字符串的末尾加上空字符
}
