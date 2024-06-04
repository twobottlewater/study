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
   //2.调用内存映射
    int *lcd_p= (int*)mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,lcdFd,0);
    if(lcd_p == MAP_FAILED)
    {
        perror("mmap error");
        return -1;
    }
    // 3.计算居中区域的起始坐标
    int startX = (800 - 320) / 2;
    int startY = (480 - 240) / 2;
    /*
     int *lcd_p[800]= (int(*)[800])mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,MAP_SHARED,lcdFd,0);
        for(int i = 0; i < 480; i++)
        {   for(int j = 0; j < 800; j++)
            {
                lcd_p[i][j] = 0xff0000;
            }
        }
         
    */
    // 4.使用二维数组表示320x240的区域
    int area[240][320];
    // 5.填充二维数组为红色
    for(int y = 0; y < 240; y++) {
        for(int x = 0; x < 320; x++) {
            area[y][x] = GREEN;
        }
    }

    // 6.将二维数组的值复制到映射的内存中
    for(int y = 0; y < 240; y++) {
        for(int x = 0; x < 320; x++) {
            lcd_p[(startY + y) * 800 + startX + x] = area[y][x];
        }
    }



 

    
    close(lcdFd);
}