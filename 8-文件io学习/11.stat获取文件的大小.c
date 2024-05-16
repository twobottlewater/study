#include "myhead.h"
/*
	获取文件大小
	struct stat
	{
		mode_t    st_mode;       //保存文件的类型，权限
		off_t     st_size;        //保存文件大小  off_t是linux用typedef取的别名
	}
*/
int main(int argc,char **argv) //主函数传参
{
	//定义struct stat类型的变量
	struct stat mystat;
	
	stat(argv[1],&mystat);  //主函数传参--》传递正确的文件路径名
	
	//打印文件大小
	printf("%s文件的大小： %ld\n",argv[1],mystat.st_size);
	return 0;
}