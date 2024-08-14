#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <linux/videodev2.h> //V4L2头文件
#include <sys/mman.h>
#include <stropts.h>
#include <unistd.h>
#include <stdbool.h>
#include "jpeglib.h"
#define W 640
#define H 480

//自定义一个结构体保存缓冲块的首地址和大小
struct camerabuf
{
	void *start; //首地址
	int somelength; //大小
};

//封装一个函数，把YUV --》转换成RGB
int yuvtorgb(int y,int u,int v)
{
	int r,g,b;
	int pix;
	r = 1164*(y-16)/1000 + 1596*(v-128)/1000;
	g = 1164*(y-16)/1000 + 813*(v-128)/1000 - 391*(u-128)/1000;
	b = 1164*(y-16)/1000 + 2018*(u-128)/1000;
	//对结果修正
	if(r>255)
		r=255;
	if(g>255)
		g=255;
	if(b>255)
		b=255;
	if(r<0)
		r=0;
	if(g<0)
		g=0;
	if(b<0)
		b=0;
	//顺便做个好事，把RGB转成ARGB，方便等会在lcd上显示
	pix=0x00<<24|r<<16|g<<8|b;
	return pix; //一个像素点的ARGB数据
}

//封装一个函数把一帧画面YUV数据转换成ARGB
/*
	yuvdata --》存放是一帧画面的YUV数据
	argbdata --》存放的是转换得到的一帧ARGB数据
*/
int allyuvtoargb(char *yuvdata,int *argbdata)
{
	/*
		yuvdata[0] -->Y1 yuvdata[1]-->U  yuvdata[3] -->V  存放argbdata[0]
		yuvdata[2] -->Y2 yuvdata[1]-->U  yuvdata[3] -->V  存放argbdata[1]
	*/
	int i,j;
	for(i=0,j=0; i<W*H; i+=2,j+=4)
	{
		argbdata[i]=yuvtorgb(yuvdata[j],yuvdata[j+1],yuvdata[j+3]);
		argbdata[i+1]=yuvtorgb(yuvdata[j+2],yuvdata[j+1],yuvdata[j+3]);
	}
}

//在来封装一个函数把一帧画面YUYV数据转换成RGB数据
int allyuvtorgb(char *yuvdata,char *rgbdata)
{
	/*
		yuvdata[0] -->Y1 yuvdata[1]-->U  yuvdata[3] -->V  存放argbdata[0]argbdata[1]argbdata[2]
		yuvdata[2] -->Y2 yuvdata[1]-->U  yuvdata[3] -->V  存放argbdata[3]argbdata[4]argbdata[5]
	*/
	int i,j;
	int pix;
	char *p;
	for(i=0,j=0; i<W*H*3 ;i+=6,j+=4) 
	{
		pix=yuvtorgb(yuvdata[j],yuvdata[j+1],yuvdata[j+3]);
		p=(char *)(&pix); //通过指针获取每个字节的数据
		rgbdata[i]=*(p+2);
		rgbdata[i+1]=*(p+1);
		rgbdata[i+2]=*p;
		
		pix=yuvtorgb(yuvdata[j+2],yuvdata[j+1],yuvdata[j+3]);
		p=(char *)(&pix);
		rgbdata[i+3]=*(p+2);
		rgbdata[i+4]=*(p+1);
		rgbdata[i+5]=*p;
	}
	return 0;
}

//封装一个函数把RGB数据保存成jpeg
int rgbsavetojpg(char *rgbdata,char *jpgpath)
{
	int i;
	//定义压缩结构体和处理错误的结构体
	struct jpeg_compress_struct mycom;
	jpeg_create_compress(&mycom);
	struct jpeg_error_mgr myerr;
	mycom.err=jpeg_std_error(&myerr);
	
	//设置压缩参数(宽，高)
	mycom.image_width=W;
	mycom.image_height=H;
	mycom.in_color_space=JCS_RGB;
	mycom.input_components=3;
	jpeg_set_defaults(&mycom);
	
	//设置压缩比例(压缩质量)
	jpeg_set_quality(&mycom,78,true);
	
	//绑定输出
	FILE *myfile=fopen(jpgpath,"w+"); //新建一张空白的jpeg文件
	if(myfile==NULL)
	{
		perror("新建jpg失败!\n");
		return -1;
	}
	jpeg_stdio_dest(&mycom,myfile);
	
	//开始压缩
	jpeg_start_compress(&mycom,true);
	
	/*
		typedef JSAMPROW *JSAMPARRAY;	
		typedef JSAMPARRAY *JSAMPIMAGE;
	*/
	JSAMPROW array[1];
	
	//把压缩后RGB的数据写入到空白的jpeg文件
	for(i=0; i<H; i++)
	{
		//把RGB数据保存到array里面
		array[0]=rgbdata+i*W*3;    //rgbdata[0]--rgbdata[W-1]  rgbdata[W]---rgbdata[2*W-1]
		jpeg_write_scanlines(&mycom,array,1);
	}
	//收尾
	jpeg_finish_compress(&mycom);
	jpeg_destroy_compress(&mycom);
	fclose(myfile);
	return 0;
}

int main()
{
	int camerafd;
	int lcdfd;
	int ret;
	int i,j;
	//打开摄像头驱动
	camerafd=open("/dev/video7",O_RDWR);
	if(camerafd==-1)
	{
		perror("打开摄像头失败!\n");
		return -1;
	}
	
	//打开液晶屏的驱动
	lcdfd=open("/dev/fb0",O_RDWR);
	if(lcdfd==-1)
	{
		perror("打开lcd失败!\n");
		return -1;
	}
	
	//映射得到lcd的首地址
	int *lcdmem=mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,lcdfd,0);
	if(lcdmem==NULL)
	{
		perror("映射lcd失败!\n");
		return -1;
	}
	//设置摄像头的采集格式
	struct v4l2_format myfmt;
	bzero(&myfmt,sizeof(myfmt));
	myfmt.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;
	myfmt.fmt.pix.width=W;
	myfmt.fmt.pix.height=H;
	myfmt.fmt.pix.pixelformat=V4L2_PIX_FMT_YUYV;
	
	ret=ioctl(camerafd,VIDIOC_S_FMT,&myfmt);
	if(ret==-1)
	{
		perror("设置采集格式失败!\n");
		return -1;
	}
	
	//申请缓冲块
	struct v4l2_requestbuffers mybuf;
	bzero(&mybuf,sizeof(mybuf));
	mybuf.count=4; //申请四个缓冲块
	mybuf.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;
	mybuf.memory=V4L2_MEMORY_MMAP;
	ret=ioctl(camerafd,VIDIOC_REQBUFS,&mybuf);
	if(ret==-1)
	{
		perror("申请缓冲块失败!\n");
		return -1;
	}
	
	//定义结构体数组存放缓冲块的信息
	struct camerabuf array[4];
	//分配你刚才申请的缓冲块
	struct v4l2_buffer buf;
	bzero(&buf,sizeof(buf));
	for(i=0; i<4; i++)
	{
		buf.index=i;
		buf.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory=V4L2_MEMORY_MMAP;
		ret=ioctl(camerafd,VIDIOC_QUERYBUF,&buf);
		if(ret==-1)
		{
			perror("分配缓冲块失败!\n");
			return -1;
		}
		//映射得到每个缓冲块的首地址
		array[i].somelength=buf.length;
		array[i].start=mmap(NULL,buf.length,PROT_READ|PROT_WRITE,MAP_SHARED,camerafd,buf.m.offset);
		if(array[i].start==NULL)
		{
			perror("映射首地址失败!\n");
			return -1;
		}
		//顺便入队，为了下一步启动摄像头做准备
		ret=ioctl(camerafd,VIDIOC_QBUF,&buf);
		if(ret==-1)
		{
			perror("入队失败!\n");
			return -1;
		}
	}
	
	//启动摄像头采集画面
	enum v4l2_buf_type mytype=V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ret=ioctl(camerafd,VIDIOC_STREAMON,&mytype);
	if(ret==-1)
	{
		perror("启动摄像头采集失败!\n");
		return -1;
	}
	
	//定义数组存放转换得到的ARGB数据
	int argbbuf[W*H];
	char rgbdata[W*H*3];
	//循环出队入队，显示视频流
	while(1)
	{
		for(i=0; i<4; i++)
		{
			buf.index=i;
			buf.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;
			buf.memory=V4L2_MEMORY_MMAP;
			//先出队
			ret=ioctl(camerafd,VIDIOC_DQBUF,&buf);
			if(ret==-1)
			{
				perror("出队失败!\n");
				return -1;
			}
			//再入队
			ret=ioctl(camerafd,VIDIOC_QBUF,&buf);
			if(ret==-1)
			{
				perror("入队失败!\n");
				return -1;
			}
			//把出队的画面数据在开发板的lcd上显示出来
			//分析得到缓冲块的首地址array[i].start --》里面存放的是YUV格式的画面数据
			//lcd的首地址lcdmem
			//仔细分析
			/*
				array[i].start[0] -->Y1
				array[i].start[1] -->U
				array[i].start[2] -->Y2
				array[i].start[3] -->V
				问题一：需要把yuv全部转成rgb，循环次数是多少？
				        依据图像的大小计算循环次数
			*/
			allyuvtoargb(array[i].start,argbbuf);
			//YUV数据转换成RGB数据
			allyuvtorgb(array[i].start,rgbdata);
			rgbsavetojpg(rgbdata,"./1.jpg"); 
			//把转换得到的ARGB数据填充到开发板的液晶屏
			//memcpy  argbbuf[0] --- argbbuf[W-1]   //第一行数据  填充到lcd起始位置  lcdmem
			//        argbbuf[W] --- argbbuf[2*W-1] //第二行数据  填充到lcd位置      lcdmem+800
			for(j=0; j<H; j++)
				memcpy(lcdmem+800*j,&argbbuf[j*W],W*4);
			
			
		}
	}
	
	//关闭摄像头
	ret=ioctl(camerafd,VIDIOC_STREAMOFF,&mytype);
	if(ret==-1)
	{
		perror("关闭摄像头采集失败!\n");
		return -1;
	}
	//收尾
	munmap(lcdmem,800*480*4);
	for(i=0; i<4; i++)
		munmap(array[i].start,array[i].somelength);
	close(camerafd);
	close(lcdfd);
	return 0;
}