#include "myhead.h"


/* 获取文件的大小
struct  stat
{
	mode_t  st_mode;
	off_t  st_size;
}


*/
int main(int argc,char **argv)
{
	struct stat mystat;
		stat(argv[1],&mystat);
	printf("%s文件的大小：%ld\n",argv[1],mystat.st_size);
	//获取文件的权限来判断
	if(mystat.st_mode&S_IRUSR)
		printf("%s文件对应当前用户是可读的\n",argv[1]);
	if(mystat.st_mode&S_IWUSR)
		printf("%s文件对应当前用户是可写的\n",argv[1]);
	if(mystat.st_mode&S_IXUSR)
		printf("%s文件对应当前用户是可执行的\n",argv[1]);
	if(mystat.st_mode&S_IRGRP)
		printf("%s文件对应同组用户是可读的\n",argv[1]);
	if(mystat.st_mode&S_IWGRP)
		printf("%s文件对应同组用户是可写的\n",argv[1]);
	
	return 0;	
}