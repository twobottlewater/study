
/*这个C语言程序主要实现了以下几个功能：

动态内存分配：程序首先定义了一个函数 get_memory，这个函数接收一个 char 类型的指针的地址
（即指针的指针）和一个整数 num。函数内部使用 malloc 函数为这个指针分配 num 字节的内存空间。
这样做的目的是能够在函数外部改变传入的指针的指向，从而使得它指向新分配的内存。
主函数（main）中的操作：
定义了一个 char 类型的指针 str 并初始化为 NULL。
调用 get_memory 函数并将 str 的地址和数字 100 作为参数传递。这将为 str 分配 100 字节的内存空间。
使用 strcpy 函数将字符串 "hello" 复制到 str 指向的内存中。这里需要注意，strcpy 是安全的因为已经为
 str 分配了足够的内存。
最后，使用 printf 函数打印 str 指向的字符串。
整个程序的目的是展示如何通过函数间接修改指针并为其分配内存，
然后在这段内存中存储和打印一个字符串。不过，需要注意的是，程序中没有释放通过 malloc 分配的内存，
这在实际编程中可能导致内存泄露。通常，在使用完动态分配的内存后，应该调用 free 函数来释放它。
此外，main 函数的标准返回类型应为 int 而不是 void，并且在结束时返回一个值，通常是 return 0;。*/



#include <stdio.h>   
#include <stdlib.h>
#include <string.h>


void get_memory(char **p,int num)
{
	*p=(char*)malloc(num);
	
}

void main(void) 
{
	char *str=NULL;
	get_memory(&str,100);
	strcpy(str,"hello");
	printf(str);
	free(str);
}
