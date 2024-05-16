#include <stdio.h>
int n;           //数据段.bss段     未初始化的全局变量
int n1=789;      //数据段.data段    已初始化的全局变量
static int m;    //数据段.bss段     static修饰的，未初始化的全局变量
static int m1=741; //数据段.data段  static修饰的，已初始化的全局变量
 
void fun()
{
	//定义变量统一fun这个函数被调用了几次
	//表示该局部变量只能被初始化一次
	static int count=0; //static局部变量,不是在栈空间，在数据段的.data段
	printf("fun被调用了%d次!\n",++count);
}

int main()
{
	int a;     //局部变量未初始化，栈空间
	int a1=78; //局部变量已初始化，栈空间
	static int b;     //数据段.bss段 static修饰的，未初始化的局部变量
	static int b1=89; //数据段.data段  static修饰的，已初始化的局部变量
	
}