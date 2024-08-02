#include <stdio.h>

int myStrcmp(const char *s1, const char *s2)
{
    const char *p = s1;
    const char *q = s2;
    int result;
    while (*p || *q)
    {
        result = *p - *q;
        if (*p++ != *q++)
            break;
    }
    if ((*p || *q) && result == 0)
    {
        result = *p - *q;
    }

    return result;
}

int main()
{
    char *a = "aBcDeF";
    char *b = "AbCdEf";
    char *c = "aacdef";
    char *d = "aBcDeF";
    printf("myStrcmp(a, b) : %d\n", myStrcmp(a, b));
    printf("myStrcmp(a, c) : %d\n", myStrcmp(a, c));
    printf("myStrcmp(a, d) : %d\n", myStrcmp(a, d));

    return 0;
}