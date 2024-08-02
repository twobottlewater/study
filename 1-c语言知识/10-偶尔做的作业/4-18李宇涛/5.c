#include <stdio.h>
/*5、编写一个程序，将两个字符串连接起来，不要用 strcat 或 strncat 函数。*/


int main() {
    char str1[100] = "Hello";
    char str2[100] = "World!";
	char *p=str1;
	char *q=str2;

	//找str1的尾部
	while (*p!= '\0') 
	{
       p++;
    }
	while (*q != '\0')
	{	
		*p=*q;
		q++;
		p++;
    }
    printf("连接后的字符串: %s\n", str1);
    return 0;
}
