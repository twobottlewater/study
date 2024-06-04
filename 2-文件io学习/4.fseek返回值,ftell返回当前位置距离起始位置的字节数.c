#include "myhead.h"
/*
	fseek的返回值跟lseek返回值意思不同
	lseek可以返回当前位置距离起始位置的字节数
	fseek返回0/-1
	因此，linux搞出了新的函数，叫做ftell返回当前位置距离起始位置的字节数
*/
int main(int argc,char **argv)
{
	FILE *myfile;
	int ret;
	long ret1;
	//打开源文件
	myfile=fopen("1.txt","r+");  //可读写
	if(myfile==NULL)
	{
		perror("打开文件失败了!\n");
		return -1;
	}
	
	//设置读写偏移
	ret=fseek(myfile,5,SEEK_SET); //起始位置往后偏移5个字节
	printf("此时fseek的返回值是: %d\n",ret);
	
	//如果我要获取当前位置距离起始位置的字节数
	ret1=ftell(myfile);
	printf("此时ftell的返回值是: %ld\n",ret1);
	//关闭文件
	fclose(myfile);
	return 0;
}