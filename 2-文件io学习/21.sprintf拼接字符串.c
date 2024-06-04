#include "myhead.h"

/*
	sprintf拼接字符串
*/
int main()
{
	int a=78;
	float b=56.9;
	char c[20]="hello";
	char name[20]="张三";
	char passwd[20]="123456";  //用户名@密码
	
	//定义数组存放拼接的结果
	char buf[100]={0};
	//拼接，把a，b，c三个变量合并成一个完整的字符串
	//sprintf(buf,"%d%f%s",a,b,c);
	//sprintf(buf,"%f####%d@@@@%s",b,a,c);	
	//sprintf(buf,"%s@%s",name,passwd);
	sprintf(buf,"%f####%d@@@@%s",b,a,c+2); //利用指针加法运算，数组c的一部分拼接了
	printf("buf is：%s\n",buf);

	return 0;
}