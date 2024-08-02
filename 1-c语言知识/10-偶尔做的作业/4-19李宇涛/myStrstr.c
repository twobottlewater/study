#include <stdio.h>

char *myStrstr(const char *haystack, const char *needle)
{
    if (!*needle)
    {
        return (char *)haystack; // 如果 needle 为空字符串，返回 haystack 的起始地址
    }

    for (; *haystack; haystack++)
    {
        const char *h = haystack;
        const char *n = needle;
        while (*h && *n && (*h == *n))
        {
            h++;
            n++;
        }
        if (!*n)
        {
            return (char *)haystack; // 如果 needle 在 haystack 中找到，返回 haystack 中 needle 的起始地址
        }
    }
    return NULL; // 如果 needle 不在 haystack 中，返回 NULL
}

int main()
{
    const char *haystack = "Hello, world!";
    const char *needle = "world";
    char *result = myStrstr(haystack, needle);
    if (result)
        printf("找到了,地址：%p\n", result);
    else
        printf("没找到\n");

    return 0;
}