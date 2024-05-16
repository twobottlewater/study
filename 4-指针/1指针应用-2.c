#include <stdio.h>
#include <string.h>
int main()
{
	int a=789;
	//定义一个int类型的指针，该指针用来存放a的地址
	//首地址：一个变量有可能在内存中占用多个字节的存储单元，首地址代表的是最低的那个地址值
	
	//指针p存放了变量a在内存中的首地址
	int *p=&a; //&取地址(获取变量a在内存中的首地址)
	
	//解引用，得到房间里面的住的人(得到地址里面存放的数据)
	printf("指针p地址中存放的数据是: %d\n",*p);
	
	/*
		总结：讨人厌的 *,不同的场合代表不同的意思
		      场合1：*表示乘法
			           a*b
		      场合2：*表示定义指针
			           int *p;
                       char *p;
                       double *p; 
  			  场合3：*表示解引用
			           *p;
	*/
	
	return 0;
}