#include <stdio.h>

int main()
{
	int buf[5];
	float b[7];
	double c[56];
	char d[47]="gec";

	//公式： 元素个数*sizeof(类型)
	printf("数组的大小: %ld  %ld  %ld  %ld\n",sizeof(buf),sizeof(b),sizeof(c),sizeof(d));	
	
	//笔试题这么考
	char buf1[]="hello"; //肉眼看到的是5个字符
	int buf2[]={78,96};  //肉眼看到的是2个整数
	
	//用strlen();可以专门求字符串的大小
	printf("%ld  %ld\n",sizeof(buf1),sizeof(buf2));
}