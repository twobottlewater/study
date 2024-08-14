#include "mycamera.h"

//定义全局变量，控制摄像头的线程任务函数
volatile int flag=1;
//封装函数把一组yuv转换得到argb
int yuvtoargb(int y,int u,int v)
{
    int r,g,b;
    int pix; //保存argb数据
    r=y+1.4075*(v-128);
    g=y-0.3455*(u-128)-0.7169*(v-128);
    b=y+1.779*(u-128);

    //修正刚才公式计算的结果
    if(r<0)
        r=0;
    if(g<0)
        g=0;
    if(b<0)
        b=0;
    if(r>255)
        r=255;
    if(g>255)
        g=255;
    if(b>255)
        b=255;

    pix=0x00<<24|r<<16|g<<8|b;
    return pix;
}

//封装函数把一帧画面全部yuyv数据转换成argb数据
int allyuvtoargb(char *yuvdata,int *argbdata)
{
    /*
        yuvdata[0]--y1
        yuvdata[1]--u
        yuvdata[2]--y2
        yuvdata[3]--v
        循环次数：由一帧画面像素点的个数(W*H个)来决定
                  每一轮循环可以得到2个像素
                  得出结论，总共需要循环(W*H)/2轮循环

    */
    int i,j;
    for(i=0,j=0; j<(W*H); i+=4,j+=2)
    {
        argbdata[j]=yuvtoargb(yuvdata[i],yuvdata[i+1],yuvdata[i+3]);
        argbdata[j+1]=yuvtoargb(yuvdata[i+2],yuvdata[i+1],yuvdata[i+3]);
    }
    return 0;
}

mycamera::mycamera()
{

}

int mycamera::camera_init()
{
    int i;
    int ret;
    //打开摄像头的驱动
    camerafd=open("/dev/video7",O_RDWR);
    if(camerafd==-1)
    {
        perror("打开摄像头失败了\n");
        return -1;
    }

    //打开液晶屏的驱动
    lcdfd=open("/dev/fb0",O_RDWR);
    if(lcdfd==-1)
    {
        perror("打开lcd失败了\n");
        return -1;
    }

    //映射得到液晶屏的首地址
    lcdmem=(int *)mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,lcdfd,0);
    if(lcdmem==NULL)
    {
        perror("映射液晶屏失败!\n");
        return -1;
    }

    //设置摄像头画面采集格式
    struct v4l2_format myfmt;
    bzero(&myfmt,sizeof(myfmt));
    myfmt.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;
    myfmt.fmt.pix.width=W;
    myfmt.fmt.pix.height=H;
    myfmt.fmt.pix.pixelformat=V4L2_PIX_FMT_YUYV; //粤嵌的摄像头是YUV格式的画面数据
    ret=ioctl(camerafd,VIDIOC_S_FMT,&myfmt);
    if(ret==-1)
    {
        perror("设置摄像头画面采集格式失败了!\n");
        return -1;
    }

    //跟摄像头申请缓冲区
    struct v4l2_requestbuffers reqbuf;
    bzero(&reqbuf,sizeof(reqbuf));
    reqbuf.count=4; //申请4个缓冲区
    reqbuf.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;
    reqbuf.memory=V4L2_MEMORY_MMAP;
    ret=ioctl(camerafd,VIDIOC_REQBUFS,&reqbuf);
    if(ret==-1)
    {
        perror("申请缓冲区失败了!\n");
        return -1;
    }

    bzero(&otherbuf,sizeof(otherbuf));
    for(i=0; i<4; i++)
    {
        otherbuf.index=i; //缓冲区的索引号，从0开始
        otherbuf.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;
        otherbuf.memory=V4L2_MEMORY_MMAP;
        ret=ioctl(camerafd,VIDIOC_QUERYBUF,&otherbuf);
        if(ret==-1)
        {
            perror("分配缓冲区失败了!\n");
            return -1;
        }
        //顺便映射得到四个缓冲块的首地址和大小
        array[i].size=otherbuf.length;
        array[i].start=mmap(NULL,otherbuf.length,PROT_READ|PROT_WRITE,MAP_SHARED,camerafd,otherbuf.m.offset);
        if(array[i].start==NULL)
        {
            perror("映射首地址失败了!\n");
            return -1;
        }
        //顺便申请画面入队
        ret=ioctl(camerafd,VIDIOC_QBUF,&otherbuf);
        if(ret==-1)
        {
            perror("画面入队失败了!\n");
            return -1;
        }
    }
    //启动摄像头
    ret=ioctl(camerafd,VIDIOC_STREAMON,&mytype);
    if(ret==-1)
    {
        perror("启动摄像头失败了!\n");
        return -1;
    }
    return 0;
}

int mycamera::camera_capture()
{
    int i,j;
    int ret;
    //定义数组把一帧画面的ARGB数据保存
    int argbbuf[W*H];
    //循环出队入队，显示摄像头拍摄的画面
    for(i=0; i<4; i++)
    {
        //出队--》把画面取出来
        otherbuf.index=i; //缓冲区的索引号，从0开始
        otherbuf.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;
        otherbuf.memory=V4L2_MEMORY_MMAP;
        ret=ioctl(camerafd,VIDIOC_DQBUF,&otherbuf);
        if(ret==-1)
        {
            perror("画面出队失败了!\n");
            return -1;
        }
        //把出队的画面在开发板的lcd上显示
        /*
            array[i].start  存放的就是一帧画面的首地址
            摄像头拍摄的画面不是RGB格式的，是YUV格式的
            YUV是什么鬼？是一种颜色编码方式 Y”表示明亮度  U和V表示颜色值
            需要把YUV转换成RGB才可以--》网上有很多计算公式
                  有些同学有选择困难症--》哪个公式画面清晰，你就用哪个
            YUYV每四个字节为一组，两个Y的值是不同的
                array[i].start[0] ---> Y1
                array[i].start[1] ---> U
                array[i].start[2] ---> Y2
                array[i].start[3] ---> V

                array[i].start[4] ---> Y1
                array[i].start[5] ---> U
                array[i].start[6] ---> Y2
                array[i].start[7] ---> V
            液晶屏要求是ARGB
        */
        //把当前出队的这一帧yuyv全部转换成argb
        allyuvtoargb((char *)(array[i].start),argbbuf);

        //把转换得到的ARGB数据填充到液晶屏
        /*
                     液晶屏            数组
            第一行  lcdmem         argbbuf[0]--argbbuf[W-1]
            第二行  lcdmem+800     argbbuf[W]--argbbuf[2*W-1]
            第三行  lcdmem+800*2   argbbuf[2*W]--argbbuf[3*W-1]
        */
        for(j=0; j<H; j++)
        {
            memcpy(lcdmem+j*800+80,&argbbuf[j*W],W*4);
        }

        //入队--》把新的画面存放到缓冲区
        ret=ioctl(camerafd,VIDIOC_QBUF,&otherbuf);
        if(ret==-1)
        {
            perror("画面入队失败了!\n");
            return -1;
        }
    }
    return 0;
}

int mycamera::camera_uninit()
{
    int i;
    int ret;
    //关闭摄像头采集
    ret=ioctl(camerafd,VIDIOC_STREAMOFF,&mytype);
    if(ret==-1)
    {
        perror("关闭摄像头失败了!\n");
        return -1;
    }

    //收尾工作
    close(camerafd);
    close(lcdfd);
    munmap(lcdmem,800*480*4);
    for(i=0; i<4; i++)
        munmap(array[i].start,array[i].size);
    return 0;
}
//线程的任务函数
void mycamera::run()
{
    while(flag)
    {
        camera_capture(); //捕捉显示画面
    }
}
