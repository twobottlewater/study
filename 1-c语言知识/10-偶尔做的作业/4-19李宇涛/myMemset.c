#include <stdio.h>

void *myMemset(void *s, int c, int n)
{
    char *p = (char *)s;
    for (int i = 0; i < n; i++)
    {
        *p++ = c;
    }
}

int main()
{

    char str[10] = "hello";
    printf("��ʼ���ַ�����%s\n", str);

    myMemset(str, 'a', 5);
    printf("myMemset����ַ�����%s\n", str);

    return 0;
}