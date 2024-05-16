#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
	int a=456;
	float b=45.6;
	double c=45.9;
	char d='@';
	
	//定义万能指针
	void *p; //野指针
	p=&a;  //后面p就不是野指针了，有明确的指向
	p=&b;
	p=&c;
	p=&d;
	
	return 0;
}