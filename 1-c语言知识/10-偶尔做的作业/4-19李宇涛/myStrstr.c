#include <stdio.h>

char *myStrstr(const char *haystack, const char *needle)
{
    if (!*needle)
    {
        return (char *)haystack; // ��� needle Ϊ���ַ��������� haystack ����ʼ��ַ
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
            return (char *)haystack; // ��� needle �� haystack ���ҵ������� haystack �� needle ����ʼ��ַ
        }
    }
    return NULL; // ��� needle ���� haystack �У����� NULL
}

int main()
{
    const char *haystack = "Hello, world!";
    const char *needle = "world";
    char *result = myStrstr(haystack, needle);
    if (result)
        printf("�ҵ���,��ַ��%p\n", result);
    else
        printf("û�ҵ�\n");

    return 0;
}