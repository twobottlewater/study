#ifndef __LCD_H
#define __LCD_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

enum Color{
   RED = 0x00ff0000, //红色
   GREEN = 0x0000ff00, //绿色
   BLACK = 0x00000000, //黑色
   WHITE = 0x00ffffff, //白色
   BLUE = 0x000000ff, //蓝色
   YELLOW = 0x00ffff00, //黄色
   
};

//全局变量的声明  注意 千万不要对变量进行赋值
struct fb_var_screeninfo varinfo;
int(*lcd_p)[800];
int lcdFd;

//函数声明
/*
@return 成功返回0 失败返回-1
@brief 初始化LCD
*/
extern int lcd_init();
/*
@return 成功返回0 失败返回-1
@brief 释放LCD资源
*/
extern int lcd_destory();
/*
@param x 横坐标
@param y 纵坐标
@param color 颜色
@return 成功返回0 失败返回-1
@brief 画一个点
@note 画点的时候 需要将点映射到LCD的坐标上
*/
extern void lcd_draw_point(int x,int y,enum Color color);
/*
@param x1 起始横坐标
@param y1 起始纵坐标
@param x2 结束横坐标
@param y2 结束纵坐标
@param color 颜色
@return 成功返回0 失败返回-1
@brief 画一条线
@note 画线的时候 需要将点的坐标映射到LCD的坐标上
*/
extern void lcd_draw_line(int x1,int y1,int x2,int y2,enum Color color);
/*
@brief 画德国国旗
*/
extern void lcd_draw_block(enum Color bcolor1,enum Color bcolor2,enum Color bcolor3);
/*
@param startX 起始横坐标
@param startY 起始纵坐标
@param drawWidth 画布宽度
@param drawHeight 画布高度
@param color 颜色
@return 成功返回0 失败返回-1
*/
extern void lcd_draw_rect(int startX,int startY,int drawWidth,int drawHeight,enum Color color);

#endif 