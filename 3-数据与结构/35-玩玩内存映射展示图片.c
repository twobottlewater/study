#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

enum Color{
   RED = 0x00ff0000, //红色
   GREEN = 0x0000ff00, //绿色
   BLUE = 0x000000ff, //蓝色
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
    //2、内存映射显示在液晶屏里面
    int *lcd_p= (int*)mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,lcdFd,0);
    if(lcd_p == MAP_FAILED)
    {
        perror("mmap error");
        return -1;
    }
    for(int i=0;i<800*480;i++)
    {
        lcd_p[i] = RED;
    }

 

    //3、关闭液晶屏文件
    close(lcdFd);
}