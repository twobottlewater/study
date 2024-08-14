#include "myhead.h"
#include "jpeglib.h" //移植得到的jpeg头文件
#define W 640  //本来我想把宽设置成800，但是摄像头默认最大的宽是640
#define H 480

//结构体，把每个缓冲块的信息组合在一个
struct bufmsg
{
	void *start;  //存放每个缓冲区的首地址
	int somelen;  //存放每个缓冲区的大小
};

//封装函数把YUV转成RGB
int yuvtorgb(int y,int u,int v)
{
	int r,g,b;
	int pix;
	r=y+1.4075*(v-128);
    g=y-0.3455*(u-128)-0.7169*(v-128);
    b=y+1.779*(u-128);
	//修正计算结果
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
	//因为lcd要求是ARGB，所以我们顺便在这里把RGB转成ARGB，方便后续使用
	pix=0x00<<24|r<<16|g<<8|b;
	return pix;
}

//封装函数把一张完整画面的YUYV数据全部转换成RGB数据
int allyuvtorgb(char *yuvdata,char *rgb)
{
	/*
		yuvdata[0] -->Y
		yuvdata[1] -->U
		yuvdata[2] -->Y
		yuvdata[3] -->V
	*/
	int i,j;
	int pix;
	char *p;
	//有W*H个像素点
	for(i=0,j=0; i<W*H*3; i+=6,j+=4) // W*H*3/6  次数
	{
		pix=yuvtorgb(yuvdata[j],yuvdata[j+1],yuvdata[j+3]);
		p=(char *)&pix;
		//根据学习的C语言指针运算规则
		//p+0-->B p+1-->G  p+2-->R  p+3 -->A
		rgb[i]=*(p+2);
		rgb[i+1]=*(p+1);
		rgb[i+2]=*(p+0);
		
		pix=yuvtorgb(yuvdata[j+2],yuvdata[j+1],yuvdata[j+3]);
		p=(char *)&pix;
		rgb[i+3]=*(p+2);
		rgb[i+4]=*(p+1);
		rgb[i+5]=*(p+0);
	}
	return 0;
}

//把RGB压缩成jpeg图片
int rgbtojpg(char *rgbdata,char *jpgfile)
{
	int i;
	//定义压缩结构体和处理错误的结构体并初始化
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
	jpeg_set_quality(&mycom,90,true);
	
	//绑定输出
	FILE *myfile=fopen(jpgfile,"w+");
	if(myfile==NULL)
	{
		perror("新建jpg图片失败了!\n");
		return -1;
	}
	jpeg_stdio_dest(&mycom,myfile);
	
	//开始压缩
	jpeg_start_compress(&mycom,true);
	
	//JSAMPARRAY类型本质上就是JSAMPROW类型的指针
	JSAMPROW row_pointer[1];
	//把压缩后的数据写入到空白的jpeg文件
	for(i=0; i<H; i++)
	{
		//把每一行的RGB数据保存到数组中
		row_pointer[0]=(JSAMPROW)(rgbdata+i*W*3);
		//一次写入一行数据
		jpeg_write_scanlines(&mycom,row_pointer,1);
	}
	
	//收尾
	jpeg_finish_compress(&mycom);
    jpeg_destroy_compress(&mycom);
	fclose(myfile);
	return 0;
}


int main()
{
	int ret;
	int i,j;
	int n=0;
	int camerafd;
	int lcdfd;
	int *lcdmem;
	char jpgname[10];
	
	//打开液晶屏的驱动
	lcdfd=open("/dev/fb0",O_RDWR);
	if(lcdfd==-1)
	{
		perror("打开液晶屏的驱动失败!\n");
		return -1;
	}
	
	//映射得到液晶屏的首地址
	lcdmem=mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,lcdfd,0);
	if(lcdmem==NULL)
	{
		perror("映射lcd失败了!\n");
		return -1;
	}
	
	//摄像头的驱动是谁？--》打开摄像头的驱动
	camerafd=open("/dev/video7",O_RDWR);
	if(camerafd==-1)
	{
		perror("打开摄像头的驱动失败!\n");
		return -1;
	}
	
	//提前设置好摄像头的采集格式--》画面宽，画面高，画面是什么格式。。。。
	struct v4l2_format myfmt;
	bzero(&myfmt,sizeof(myfmt));
	myfmt.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;
	myfmt.fmt.pix.width=W;  
	myfmt.fmt.pix.height=H;
	myfmt.fmt.pix.pixelformat=V4L2_PIX_FMT_YUYV; //yuv格式
	ret=ioctl(camerafd,VIDIOC_S_FMT,&myfmt);
	if(ret==-1)
	{
		perror("设置采集格式失败了!\n");
		return -1;
	}
	
	//跟摄像头的驱动申请缓冲区
	struct v4l2_requestbuffers mybuf;
	bzero(&mybuf,sizeof(mybuf));
	mybuf.count=4;
	mybuf.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;
	mybuf.memory=V4L2_MEMORY_MMAP;
	ret=ioctl(camerafd,VIDIOC_REQBUFS,&mybuf);
	if(ret==-1)
	{
		perror("申请缓冲区失败!\n");
		return -1;
	}
	
	//定义结构体数组，存放4个缓冲区的信息
	struct bufmsg array[4];
	//分配刚才你申请的4个缓冲区
	struct v4l2_buffer otherbuf;
	for(i=0; i<4; i++)
	{
		bzero(&otherbuf,sizeof(otherbuf));
		otherbuf.index=i;
		otherbuf.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;
		otherbuf.memory=V4L2_MEMORY_MMAP;
		ret=ioctl(camerafd,VIDIOC_QUERYBUF,&otherbuf);
		if(ret==-1)
		{
			perror("分配缓冲区失败!\n");
			return -1;
		}
		
		//顺便映射得到4个缓冲块的首地址(方便后面取出画面数据)
		array[i].somelen=otherbuf.length;
		array[i].start=mmap(NULL,otherbuf.length,PROT_READ|PROT_WRITE,MAP_SHARED,camerafd,otherbuf.m.offset);
		if(array[i].start==NULL)
		{
			perror("映射缓冲区首地址失败!\n");
			return -1;
		}
		
		//立马申请入队--》下一步摄像头立马就要启动采集了
		ret=ioctl(camerafd,VIDIOC_QBUF,&otherbuf);
		if(ret==-1)
		{
			perror("入队失败!\n");
			return -1;
		}
	}
	
	//启动摄像头采集
	enum v4l2_buf_type mytype;
	mytype=V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ret=ioctl(camerafd,VIDIOC_STREAMON,&mytype);
	if(ret==-1)
	{
		perror("启动摄像头失败!\n");
		return -1;
	}
	
	char rgbbuf[W*H*3];
	fd_set myset;
	//循环出队，入队显示视频流
	while(1)
	{
		FD_ZERO(&myset);
		FD_SET(camerafd,&myset); //监测摄像头
		//用多路复用监测摄像头是否有数据可读，有数据可读我才来出队
		ret=select(camerafd+1,&myset,NULL,NULL,NULL);
		if(ret>0)
		{
			for(i=0; i<4; i++)
			{
				bzero(&otherbuf,sizeof(otherbuf));
				otherbuf.index=i;
				otherbuf.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;
				otherbuf.memory=V4L2_MEMORY_MMAP;
				//出队
				ret=ioctl(camerafd,VIDIOC_DQBUF,&otherbuf);
				if(ret==-1)
				{
					perror("出队失败!\n");
					return -1;
				}
				//把出队的画面数据保存成jpeg图片
				//array[i].start里面保存的就是一张张画面数据
				//画面数据是YUV格式,jpeg图片要求是RGB数据压缩得到的
				//把YUV格式转换成RGB格式
				allyuvtorgb(array[i].start,rgbbuf);
				//把刚才转换得到的RGB数据压缩成jpeg图片
				sprintf(jpgname,"%d.jpg",n++);
				rgbtojpg(rgbbuf,jpgname);
				sleep(1);
				//入队
				ret=ioctl(camerafd,VIDIOC_QBUF,&otherbuf);
				if(ret==-1)
				{
					perror("入队失败!\n");
					return -1;
				}
			}
		}		
	}
}