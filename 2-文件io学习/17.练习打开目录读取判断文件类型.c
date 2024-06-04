#include "myhead.h"

int main(int argc,char **argv)
{
	DIR *mydir;
	//打开目录
	mydir=opendir(argv[1]);
	if(mydir==NULL)
	{
		perror("打开目录失败了!\n");
		return -1;
	}
	
	//每个人打开的目录都不一样(目录中存放文件个数不一样)
	//循环读取目录
	struct dirent *mydirent;
	while((mydirent=readdir(mydir))!=NULL)
	{
		//判断文件类型
		if(mydirent->d_type==DT_REG) //普通文件
		{
			//进一步判断是不是bmp或者txt
			//判断子串
			if(strstr(mydirent->d_name,".bmp")!=NULL)
				printf("%s是个bmp图片!\n",mydirent->d_name);
			if(strstr(mydirent->d_name,".txt")!=NULL)
				printf("%s是个记事本!\n",mydirent->d_name);
		}
		else if(mydirent->d_type==DT_DIR) //目录
		{
			printf("你现在遍历的这个是目录: %s\n",mydirent->d_name);
		}
	}
}