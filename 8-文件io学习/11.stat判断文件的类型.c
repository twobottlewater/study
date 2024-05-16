#include "myhead.h"
/*
	判断文件的类型
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
	
	//获取文件的类型，来判断
	//方法1；按位与运算
	if((mystat.st_mode&S_IFMT)==S_IFREG)  //是个普通文件
		printf("%s文件是个普通文件!\n",argv[1]);
	if((mystat.st_mode&S_IFMT)==S_IFDIR)  //是个目录
		printf("%s文件是个目录!\n",argv[1]);	
		
	//方法2：带参数的宏定义来判断
	if(S_ISDIR(mystat.st_mode)) 
		printf("%s文件是个目录!\n",argv[1]);
	if(S_ISREG(mystat.st_mode)) 
		printf("%s文件是个普通文件!\n",argv[1]);
	
	return 0;
}