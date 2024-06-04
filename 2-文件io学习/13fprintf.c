#include "myhead.h"


/*
fprintf可以把不同的类型数据写入到文件中
*/
	
int main(int argc,char **argv)
{
	FILE *srcfile;
	int year=2000;
	double score=85.5;
	char buf[50]="张三的出生年份是:";
	//打开文件
	srcfile=fopen(argv[1],"r+");//可读可写的方式
	if(srcfile==NULL)
	{
		perror("打开源文件失败了!\n");
		return -1;
	}
		
	fprintf(srcfile,"%s%d,他考了多少分:%lf分",buf,year,score);

	
	
	fclose(srcfile);
	
	return 0;
}