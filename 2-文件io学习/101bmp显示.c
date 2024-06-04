#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    //1、打开液晶屏文件
    int lcdFd = open("/dev/fb0", O_RDWR);
    if(lcdFd == -1)
    {
        perror("open lcd  error");
        return -1;
    }
    //2、打开图片文件
    int bmpFd = open("1.bmp", O_RDONLY);
    if(bmpFd == -1)
    {
        perror("open bmp error");
        return -1;
    }
    //3、读取图片文件 
    char bmpbuf[800*480*3] = {0}; //一共是800*480个像素点，每个像素点3个字节
    read(bmpFd, bmpbuf, sizeof(bmpbuf));

    //将图像中的每个像素点 BGR 转换为 ARGB
    int tempbuf[800*480] = {0};//存储转换之后的颜色数据
    for(int i=0,j=0; i<800*480; i++,j+=3)
    {
        tempbuf[i] =0x00<<24 | bmpbuf[j+2]<<16 |  bmpbuf[j+1]<<8 |  bmpbuf[j] ;
    }

    //4、将读取到的图片数据写入液晶屏文件
    write(lcdFd,tempbuf,sizeof(tempbuf));

    //5、关闭液晶屏文件
    close(lcdFd);

    //6、关闭图片文件
    close(bmpFd);
}