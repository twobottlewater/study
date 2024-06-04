#include <stdio.h>

//定义全局变量

int main()
{
	char a='i';
	char *p=&a;
	char **q=&p;

	printf("a的地址是: %p\n",&a);
	printf("p的地址是: %p\n",&p);

	printf("*q是: %p\n",*q);
	printf("**q是: %c\n",**q);
	printf("p是: %p\n",p);
	printf("*p是: %c\n",*p);

	return 0;
}
