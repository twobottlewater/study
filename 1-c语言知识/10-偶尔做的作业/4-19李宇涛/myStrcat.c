#include <stdio.h>

char *myStrcat(char *dest, char *src)
{
    char *p = dest, *q = src;
    while (*(++p))
        ;
    while (*q)
    {
        *p++ = *q++;
    }
    *(++p) = '\0';
    return dest;
}

int main()
{
    char a[30] = "String(1)";
    char b[] = "string(2)";
    printf("myStrcat函数未运行前：%s\n", a);
    printf("myStrcat函数运行后：%s\n", myStrcat(a, b));
    return 0;
}