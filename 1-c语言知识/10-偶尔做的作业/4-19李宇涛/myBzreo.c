#include <stdio.h>

void myBzero(void *s, int n)
{
    char *p = (char *)s;
    for (int i = 0; i < n; i++)
    {
        *p++ = 0;
    }
}

int main()
{
    char str[10] = "hello";
    printf("��ʼ���ַ�����%s\n", str);

    myBzero(str, 5);
    printf("������ַ�����%s\n", str);
    return 0;
}