#include <stdio.h>
#include<stdbool.h>
#include<string.h>
#include<strings.h>
struct A
{
	char t:4;//指定t占用4个二进制位
	char k:8;//指定t占用8个二进制位
	unsigned short i:8;
	unsigned long m; //用了long就是8字节对齐了
};


int main()
{
	printf("long's sizeof is%ld\n",sizeof(long));
	printf("shrot's sizeof is%ld\n",sizeof(short));
	printf("%ld\n",sizeof(struct A));  //这里就应该是16了
	
	return 0;
	
}
