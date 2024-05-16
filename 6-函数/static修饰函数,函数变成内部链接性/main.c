#include <stdio.h>

/*
	我自己这个.c文件没有定义fun这个函数
	main.c想要使用fun.c中定义的fun函数--》可以使用
*/
//添加外部声明--》不要紧张，后面单独讲该知识点
extern void fun();
int main()
{
	fun();
}