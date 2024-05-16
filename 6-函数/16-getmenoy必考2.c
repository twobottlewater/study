#include <stdio.h>   
#include <stdlib.h>
#include <string.h>
char *get_memory(void)
{
	char p[]="hello world";
	return p;
}

void main(void) 
{
	char *str=NULL;
	str=get_memory();

	printf(str);

}
/*打印不了，因为char p[]数组的指针会在函数运行完之后会自动释放
不能正常返回*/
