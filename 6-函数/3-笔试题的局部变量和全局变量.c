#include <stdio.h>

//定义全局变量
int n=45;  //.c文件中所有的函数都共享同一个全局变量

int fun(int n) //fun自己的局部
{
	n+=12;  //fun自己的局部
	printf("n is: %d  fun的n地址是%p\n",n,&n); //fun自己的局部
	return 0;
}

void otherfun()
{
	n+=12;  //全局
	printf("n is: %d  otherfun的地址是%p\n",n,&n); //全局
}
int main()
{
	fun(n);  //传值，全局
	otherfun();//这里是关键,他把全局的值直接改变了,他不是传值进去


	printf("n is: %d  第一次printf 是%p\n",n,&n);  //全局
	int n=45; //main自己的局部
	fun(n);  //main自己的局部  然后把main的局部变量45传进去
	otherfun(); 		//还是全局的变量现在已经是57了然后加多一次成了69
	printf("n is: %d第二次printf的地址是%p\n",n,&n);
	return 0;
}
