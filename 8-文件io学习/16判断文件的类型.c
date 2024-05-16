#include "myhead.h"

int main(int argc,char **argv)
{
	DIR *mydir;
	mydir=opendir(argv[1]);
	if(mydir==NULL)
	{
		perror("打开目录失败了\n");
		return -1;
	}
	struct dirent *mydirent;
	while((mydirent=readdir(mydir))!=NULL)
	{
		if(mydirent->d_type==DT_REG)
		{
		//判断文件类型
		if(strstr(mydirent->d_name,".bmp")!=NULL)
			printf("%s是个bmp图片\n",mydirent->d_name);
		if(strstr(mydirent->d_name,".txt")!=NULL)
			printf("%s是个txt文本\n",mydirent->d_name);
		}
		
		else if(mydirent->d_type==DT_DIR)
			printf("你现在遍历的这个是目录:%s\n",mydirent->d_name);
	}
	
	return 0;
}