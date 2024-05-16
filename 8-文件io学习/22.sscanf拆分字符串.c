#include "myhead.h"

/*
	sscanf拆分字符串
*/
int main()
{
	//定义三个变量保存年月日
	int year,month,day;
	
	char buf[20]="2023@7#28";
	//sscanf把buf里面的内容拆分出来(按照%d-%d-%d格式)，分别存放到&year,&month,%day
	sscanf(buf,"%d@%d#%d",&year,&month,&day);
	printf("年：%d 月： %d  日： %d\n",year,month,day);
	return 0;
}