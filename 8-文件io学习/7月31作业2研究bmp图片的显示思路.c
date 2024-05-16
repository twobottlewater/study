#include "myhead.h"
/*
	作业2：研究bmp图片的显示思路
	  bmp特点：
	       每个像素点占3个字节 BGR
		   最前面有54字节的头信息，从55字节开始才是真实的BGR数据
		   54头信息存放图片的格式大小这些信息
		         800*480*3本来结果是1152000个字节
				 实际图片大小是1152054个字节
		   微软发明的图片格式，存储的时候是上下颠倒
      液晶屏要求每个像素点4个字节，分别是ARGB
	  开发板屏幕分辨率800*480
	
*/
int main(int argc,char **argv)
{
	int bmpfd;
	int lcdfd;
	int i,x,y;
	//定义数组把整个图片的BGR数据存放起来
	char bmpbuf[800*480*3]; //char类型占1个字节
	//定义数组把转换得到的ARGB数据存放起来
	int lcdbuf[800*480]; //int占4字节
	
	//打开bmp图片和液晶屏
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
	
	//最前面有54字节的头信息，从55字节开始才是真实的BGR数据
	//跳过最前面的54字节，从55个字节开始读取bmp图片的像素点颜色值
	lseek(bmpfd,54,SEEK_SET);
	read(bmpfd,bmpbuf,800*480*3);
	
	//把刚才读取的数据写入到液晶屏中
	/*
		液晶屏是ARGB
		图片是BRG
		三个字节如何变成四个字节--》C语言的按位或跟左移配合
		思路1：
		二进制数
		     0100 1011
			 1010 1010<<8  位或
			 1001 1011<<16 位或
			 0000 0000<<24 位或
			                                 0100 1011
			                       1010 1010 0000 0000  位或
                         1001 1011 0000 0000 0000 0000	位或
               0000 0000 0000 0000 0000 0000 0000 0000	位或
			   
	    领悟：左移和按位或可以把数据合并拼接
		思路2：利用指针的加法运算来实现
		       bmpbuf[0] --》B 
			   bmpbuf[1] --》G  
			   bmpbuf[2] --》R
			   char otherbuf[800*480*4]={0};
			   正确答案如下，A在最高字节
			   otherbuf[0]     B
			   otherbuf[1]     G
			   otherbuf[2]     R
			   otherbuf[3]     A
			   错误答案，刚好写反了
			   otherbuf[0]   A  
			   otherbuf[1]   R  
			   otherbuf[2]   G  
			   otherbuf[3]   B  
	*/
	//把3个字节的BRG转换成4个字节的ARGB
	for(i=0; i<800*480; i++)
		lcdbuf[i]=0x00<<24|bmpbuf[3*i+2]<<16|bmpbuf[3*i+1]<<8|bmpbuf[3*i];

	write(lcdfd,tempbuf,800*480*4);
	//把刚才转换得到的ARGB数据写入到液晶屏
	write(lcdfd,lcdbuf,800*480*4);
	
	//关闭
	close(bmpfd);
	close(lcdfd);
	return 0;
}