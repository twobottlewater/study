#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
	int *p1;
	char *p2;
	double *p3;
	float *p4;
	
	//在64位ubuntu系统上，所有的指针都是8字节
	printf("sizeof(p1) is: %ld\n",sizeof(p1));
	printf("sizeof(p2) is: %ld\n",sizeof(p2));
	printf("sizeof(p3) is: %ld\n",sizeof(p3));
	printf("sizeof(p4) is: %ld\n",sizeof(p4));
	return 0;
}