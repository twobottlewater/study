#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
	//定义指针立马给它申请分配堆空间
	//void *跟其他指针之间可以自由转换(写不写强转都无所谓)
	int *p=malloc(20);	//注意：20单位是字节
	char *p1=malloc(20);
	double *p2=malloc(10*sizeof(double));
	float *p3=malloc(10*sizeof(float));
	//任何类型 *p=malloc(字节数);
	return 0;
}