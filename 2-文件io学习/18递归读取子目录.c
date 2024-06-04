#include "myhead.h"

//封装一个递归函数
int myreaddir(const char *dirpath)
{
	char allpth[100]={0};
	//打开目录
	DIR *mydir;
	//打开目录
	mydir=opendir(dirpath);
	if(mydir==NULL)
	{
		perror("打开目录失败了!\n");
		return -1;
	}
	
	
	//循环读取目录
	struct dirent *mydirent;
	while((mydirent=readdir(mydir))!=NULL)
	{
		//排除掉小数点和..
		if(strcmp(mydirent->d_name,".")==0 ||	strcmp(mydirent->d_name,"..")==0  )
			continue;
		
		//判断文件类型
		if(mydirent->d_type==DT_REG) //普通文件
		{
			bzero(allpth,100);
			sprintf(allpth,"%s/%s",dirpath,mydirent->d_name);
			printf("现在遍历的文件是%s\n",allpth);
		}
		else if(mydirent->d_type==DT_DIR) //目录
		{
			bzero(allpth,100);
			sprintf(allpth,"%s/%s",dirpath,mydirent->d_name);
			myreaddir(allpth);
		}
	}
	return 0;
}


int main(int argc,char **argv)
{
	//调用函数
	myreaddir("./123");
	return 0;
}