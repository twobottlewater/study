#include "myhead.h"


/*
fread 和 fwrite 来拷贝文件
*/
	
int main(int argc,char **argv)
{
	FILE *srcfile;
	FILE *destfile;
	ssize_t ret;
	//定于数组存内容
	char buf[1024*1024];

	srcfile=fopen(argv[1],"r+");//可读可写的方式
	if(srcfile==NULL)
	{
		perror("打开源文件失败了!\n");
		return -1;
	}
	
	destfile=fopen(argv[2],"w+");
	if(destfile==NULL)
	{
		perror("鎵撳紑澶辫触\n");
		return -1;
	}
	
	while(1)
	{
		//读取
		ret=fread(buf,1,1024*1024,srcfile);
		//写出去
		
		if(ret==0)
		break;
	
		fwrite(buf,1,ret,destfile);
		if(feof(srcfile))
		break;
	}
	fclose(srcfile);
	fclose(destfile);
	return 0;
}