#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

enum Color{
   RED = 0x00ff0000, //红色
   GREEN = 0x0000ff00, //绿色
   BLACK = 0x00000000, //黑色
   YELLOW = 0x00ffff00, //黄色
};

int main()
{
    //1、打开液晶屏驱动文件 
    int lcdFd = open("/dev/fb0",O_RDWR);
    if(lcdFd == -1)
    {
        perror("open lcd error");
        return -1;
    }
    //2、将像素点数据写入液晶屏文件中 ---往液晶屏设备中填充像素点
    //int color = GREEN; //一个像素点
    int buf[800*480] = {0};
  
    for(int i=0; i<800*160; i++)
     {
    buf[i] = BLACK;
    }

    // 填充红色区域
    for(int i=800*160; i<800*320; i++) {
        buf[i] = RED;
    }

    // 填充黄色区域
    for(int i=800*320; i<800*480; i++) {
        buf[i] = YELLOW;
    }

    write(lcdFd,buf,800*480*4);

    //3、关闭液晶屏文件
    close(lcdFd);
}