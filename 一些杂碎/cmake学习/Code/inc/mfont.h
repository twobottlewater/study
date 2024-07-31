#ifndef __MFONT_H
#define __MFONT_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <fcntl.h>
#include "font.h"
#include "lcd.h"



/*
text:你要显示的文本
pixelSize:字体的大小  最大为72
outFrameWidth:输出框的宽度
outFrameHeight:输出框的高度
outFrameColor:输出框的背景颜色
fontPosX:文本相对于输出框的位置 X
fontPosY:文本相对于输出框的位置 Y
fontColor：文本的颜色
frameToLcdPosX:输出框相对于液晶屏的位置坐标X
frameToLcdPosY:输出框相对于液晶屏的位置坐标Y
*/
void font_show(char *text,int pixelSize,int outFrameWidth,int outFrameHeight,int outFrameColor,int fontPosX,int fontPosY,int fontColor,int frameToLcdPosX,int frameToLcdPosY);
void showbitmap(bitmap *bm, int x, int y);
#endif