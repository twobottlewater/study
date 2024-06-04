#include<stdio.h>

int main()
{
    "abcd";

    //"abcd"是匿名数组的首地址，也就是代表'a'的地址
    //%s打印的时候，printf获取 'a'的地址，然后逐个打印后面的字符 直到遇到'\0'
    printf("%s\n","abcd");

    printf("%c\n",*("abcd"));
    printf("%c\n","abcd"[0]);

    printf("%c\n",*("abcd" + 1));
    printf("%c\n","abcd"[1]);

    //*("abcd" + 1) = 'y'; 运行的时候会发送段错误，因为你尝试修改常量的内存空间，系统不允许这样做

	return 0;
}