#include "myhead.h"

/*
	有名管道只能在纯粹的linux环境创建
*/

int main()
{
	int ret;
	int fd;
	char buf[100];
	
	//判断有名管道是否已经存在
	if(access("/mnt/hgfs/share/myfifo",F_OK)!=0) //不存在
	{
		//创建一个有名管道
		ret=mkfifo("/mnt/hgfs/share/myfifo",0777);
		if(ret==-1)
		{
			perror("新建有名管道失败了!\n");
			return -1;
		}
	}
	return 0;
}