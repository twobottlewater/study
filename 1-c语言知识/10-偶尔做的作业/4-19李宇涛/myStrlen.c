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
    printf("���ַ����ĳ���Ϊ:%d\n", myStrlen(str));

    return 0;
}