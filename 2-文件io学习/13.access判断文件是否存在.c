#include "myhead.h"
/*
	access判断文件是否存在
*/
int main(int argc,char **argv) //主函数传参
{
	//判断参数个数
	if(argc==2)
	{
		//主函数传递文件的路径名
		//判断文件是否存在
		if(access(argv[1],F_OK)==0)
			printf("%s文件存在!\n",argv[1]);
		else
			printf("%s文件不存在!\n",argv[1]);
		
		//判断文件是否可读
		if(access(argv[1],R_OK)==0)
			printf("%s文件是可读的!\n",argv[1]);
		else
			printf("%s文件不可读的!\n",argv[1]);
	}
	else
	{
		printf("老铁，你敲快了，忘记传递参数  ./程序名 文件路径!\n");
	}
	
		
	return 0;
}