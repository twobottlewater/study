#include "myhead.h"

//在linux内核中有定义一个全局变量，是个二级指针
//该指针存放了当前进程的环境变量
extern const char **environ;
int main(int argc,char **argv)
{
	int i;
	if(argc<2)
	{
		printf("对不起，你忘记传递参数了!\n");
		return -1;
	}
	else
	{
		//打印当前进程的环境变量
		for(i=0; environ[i]!=NULL; i++)
			printf("当前进程的环境变量是: %s\n",environ[i]);  //*(environ+i)
	}
	
}