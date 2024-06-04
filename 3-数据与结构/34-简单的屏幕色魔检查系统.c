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
    //2、定义一个数组，保存三种颜色
    enum Color colors[] = {RED, GREEN, BLUE};
    int buf[800*480] = {0};
    int colorCount = sizeof(colors) / sizeof(colors[0]);

    while (1)
    {
        for (int i = 0; i < colorCount; ++i) 
        {
            enum Color color = colors[i];
            for (int j = 0; j < 800*480; ++j) {
                buf[j] = color;
            }
            write(lcdFd, buf, 800*480*4); // 假设颜色是32位，即4字节
            sleep(3); // 等待3秒
        }

    }
  
   

    write(lcdFd,buf,800*480*4);

    //3、关闭液晶屏文件
    close(lcdFd);
}