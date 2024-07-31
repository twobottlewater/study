#include "../inc/lcd.h"


//接口函数
//液晶屏的初始化
int lcd_init()
{
    //1、打开液晶屏
    lcdFd = open("/dev/fb0",O_RDWR);
    if(lcdFd == -1)
    {
        perror("open lcd error");
        return -1;
    }
    //2、获取液晶屏设备的硬件参数
    if(ioctl(lcdFd, FBIOGET_VSCREENINFO, &varinfo) != 0)
    {
        perror("获取LCD设备可变属性信息失败");
        return -1;
    }
    //800   480
    printf("[可见区分辨率]: %d×%d\n", varinfo.xres, varinfo.yres);
    printf("[虚拟区分辨率]: %d×%d\n", varinfo.xres_virtual, varinfo.yres_virtual);
    printf("[色深]: %d bits\n", varinfo.bits_per_pixel); //32位   转成4个字节 32/8  
    //3、进行内存映射
    lcd_p = (int(*)[800])mmap(NULL,varinfo.xres*varinfo.yres*varinfo.bits_per_pixel/8,PROT_READ|PROT_WRITE,MAP_SHARED,lcdFd,0);
    if(lcd_p == MAP_FAILED)
    {
        perror("mmap error");
        return -1;
    }
    //int lcd_p[480][800]
}

int lcd_destory()
{
    //解除内存映射
    munmap(lcd_p, varinfo.xres*varinfo.yres*varinfo.bits_per_pixel/8);
    close(lcdFd);
}

//画一个点
void lcd_draw_point(int x,int y,enum Color color)
{
    lcd_p[y][x] = color;
}

//画一个线段
void lcd_draw_line(int x1,int y1,int x2,int y2,enum Color color)
{
    //画线算法
    //1、确定线的方向
    int dx = x2 - x1;
    int dy = y2 - y1;
    //2、确定步长
    int step = (dx>=0)?1:-1;
    //3、确定初始值
    int x = x1;
    int y = y1;
    //4、确定终止值
    int endx = (dx>=0)?x2:x1;
    int endy = (dy>=0)?y2:y1;
    //5、画线
    while(x!=endx || y!=endy)
    {
        lcd_draw_point(x,y,color);
        x += step;
        y += step;
    }
}
//画德国国旗
void lcd_draw_block(enum Color bcolor1,enum Color bcolor2,enum Color bcolor3)
{
    for(int j=0;j<480;j++)
    {
        for(int i=0;i<800;i++)
        {
            if(j<480/3)
            {
                lcd_p[j][i] = bcolor1;
            }
            else if(j<480/3 *2)
            {
                lcd_p[j][i] = bcolor2;
            }
            else
            {
                lcd_p[j][i] = bcolor3;
            }
        }
    }
    sleep(1);
}

void lcd_draw_rect(int startX,int startY,int drawWidth,int drawHeight,enum Color color)
{
    for(int j=0; j<drawHeight; j++)
    {
        for(int i=0; i<drawWidth; i++)
        {
            lcd_p[startY+j][startX+i] = color;
        }
    }
}


//开机显示白色背景的函数
void lcd_draw_white_bg()
{
    for(int j=0; j<480; j++)
    {
        for(int i=0; i<800; i++)
        {
            lcd_p[j][i] = WHITE;
        }
    }
}