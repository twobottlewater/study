#include <stdio.h>



int main()
{ 
	/*
	指针数组
	      char *p[10]   //p是数组名
	数组指针
	      char (*p)[10] //p是指针名
*/
	int a=78;
	int b=98;
	int c=66;
	//指针数组--》中心词是数组--》想到公式  类型 数组名[元素个数]--》类型必须是指针
	int *buf[3];
	char buf1[10]="hello";
	char buf2[10]="world";
	char buf3[20]="gec";

	buf[0]=&a;
	buf[1]=&b;
	buf[2]=&c;

	//访问数组
	for(size_t i=0; i<3; i++)
	{
		printf("buf[%d]存放的地址值 is: %p\n",i,buf[i]);
		printf("*buf[%d]对应的值 is: %d\n",i,*(buf[i]));
	}

	char *otherbuf[3]; //可以存放3个char *
	otherbuf[0]=buf1;  //第一个char *
	otherbuf[1]=buf2;  //第二个char *
	otherbuf[2]=buf3;  //第三个char *
	for(size_t i=0; i<3; i++)
	{
		printf("otherbuf[%d]存放的地址值 is: %p\n",i,otherbuf[i]);
		printf("*otherbuf[%d]对应的值 is: %c\n",i,*(otherbuf[i]));
		printf("otherbuf[%d]当成字符串打印：%s\n",i,otherbuf[i]);
	}
	return 0;
}
 

