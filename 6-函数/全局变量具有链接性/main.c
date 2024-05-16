#include <stdio.h>

/*
	我自己这个.c文件没有定义全局变量n
	main.c想要使用fun.c中定义的全局变量--》可以使用
*/
//添加外部声明--》不要紧张，后面单独讲该知识点
extern int n;
extern void fun();
int main()
{
	printf("我要使用fun中的那个全局变量 %d\n",n);
	fun();
}