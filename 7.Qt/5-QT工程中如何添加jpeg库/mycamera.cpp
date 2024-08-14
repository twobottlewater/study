#include "mycamera.h"
//封装函数把一组yuv转换得到argb
int yuvtorgb(int y,int u,int v)
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
    jpeg_set_quality(&mycom,90,(boolean)true);

    //绑定输出
    FILE *myfile=fopen(jpgfile,"w+");
    if(myfile==NULL)
    {
        perror("新建jpg图片失败了!\n");
        return -1;
    }
    jpeg_stdio_dest(&mycom,myfile);

    //开始压缩
    jpeg_start_compress(&mycom,(boolean)true);

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
    //定义数组把一帧画面的RGB数据保存
    char rgbbuf[W*H*3];
    int n=0;
    char jpgname[10];
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
        //把出队的画面数据保存成jpeg图片
        //array[i].start里面保存的就是一张张画面数据
        //画面数据是YUV格式,jpeg图片要求是RGB数据压缩得到的
        //把YUV格式转换成RGB格式
        allyuvtorgb((char *)(array[i].start),rgbbuf);
        //把刚才转换得到的RGB数据压缩成jpeg图片
        sprintf(jpgname,"%d.jpg",n++);
        rgbtojpg(rgbbuf,jpgname);
        sleep(1);

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
