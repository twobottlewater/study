#include <stdio.h>

int myStrlen(const char *s)
{
    const char *p = s;
    int cnt = 0;
    while (*p)
    {
        cnt++;
        p++;
    }
    return cnt;
}

int main()
{
    char str[20] = "hello";
    printf("该字符串的长度为:%d\n", myStrlen(str));

    return 0;
}