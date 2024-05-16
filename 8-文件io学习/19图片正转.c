#include "myhead.h"
/*
	
	
*/
int main(int argc,char **argv)
{
	int bmpfd;
	int lcdfd;
	int tempbuf[800*480]; //临时存放图片翻转之后的数据
	int i,x,y;
	char bmpbuf[800*480*3]; //char类型占1个字节
	int lcdbuf[800*480]; //int占4字节
	
	bmpfd=open("/1.bmp",O_RDWR);
	if(bmpfd==-1)
	{
		perror("打开图片失败了!\n");
		return -1;
	}
	lcdfd=open("/dev/fb0",O_RDWR);
	if(lcdfd==-1)
	{
		perror("打开lcd失败了!\n");
		return -1;
	}
	lseek(bmpfd,54,SEEK_SET);
	read(bmpfd,bmpbuf,800*480*3);
	
	for(i=0; i<800*480; i++)
	lcdbuf[i]=0x00<<24|bmpbuf[3*i+2]<<16|bmpbuf[3*i+1]<<8|bmpbuf[3*i];
		//把颠倒的画面翻转过来
	for(x=0; x<800; x++)
	{
		for(y=0; y<480; y++)
			//lcdbuf[(479-y)*800+x]=lcdbuf[y*800+x];错误的，不应该自己赋值给自己
			tempbuf[(479-y)*800+x]=lcdbuf[y*800+x];
	}
	write(lcdfd,tempbuf,800*480*4);
	//关闭
	close(bmpfd);
	close(lcdfd);
	return 0;
}