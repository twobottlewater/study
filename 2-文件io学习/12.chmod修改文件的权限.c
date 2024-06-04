#include "myhead.h"
/*
	修改文件的权限
	struct stat
	{
		mode_t    st_mode;       //保存文件的类型，权限
		off_t     st_size;        //保存文件大小  off_t是linux用typedef取的别名
	}
*/
int main(int argc,char **argv) //主函数传参
{
	//直接修改文件的权限
	chmod(argv[1],0655);
	//定义struct stat类型的变量
	struct stat mystat;
	
	stat(argv[1],&mystat);  //主函数传参--》传递正确的文件路径名
	//获取文件的权限，来判断
	if(mystat.st_mode&S_IRUSR)
		printf("%s文件对应当前用户是可读的!\n",argv[1]);
	if(mystat.st_mode&S_IWUSR)
		printf("%s文件对应当前用户是可写的!\n",argv[1]);
	if(mystat.st_mode&S_IXUSR)
		printf("%s文件对应当前用户是可执行的!\n",argv[1]);
	return 0;
}