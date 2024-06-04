#include "myhead.h"

int main(int argc,char **argv)
{
	int ret;
	//判断某个文件是否存在
	ret=access(argv[1],F_OK);
	if(ret==0)
		printf("%s文件是存在的！\n",argv[1]);
	else
		printf("%s文件是不存在的！\n",argv[1]);
}