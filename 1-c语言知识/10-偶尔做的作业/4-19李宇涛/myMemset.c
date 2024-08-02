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
    printf("³õÊ¼»¯×Ö·û´®£º%s\n", str);

    myMemset(str, 'a', 5);
    printf("myMemsetºóµÄ×Ö·û´®£º%s\n", str);

    return 0;
}