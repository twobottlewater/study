#include "../inc/mfont.h"
#include "../inc/log.h"

void showbitmap(bitmap *bm, int x, int y)
{
    // 准备好LCD设备（如果多次显示，应该只做一遍）

    // 字体的信息：
    // bm->width;
    // bm->height;
    // bm->byteperpixel;
    // bm->map; // 指向RGB数据，没有上下颠倒，也没有一行4字节倍数的约束，就是纯粹的RGB

    //printf("width:%d, height:%d, byteperpixel:%d\n", bm->width, bm->height, bm->byteperpixel);

    for(int j=0; j<bm->height; j++)
    {
        for(int i=0; i<bm->width; i++)
        {         
            int bgrIndex = (j * bm->width + i) * 4;
            lcd_p[j+y][i+x] =  (bm->map[bgrIndex + 3] << 24) | (bm->map[bgrIndex + 2] << 16) | (bm->map[bgrIndex + 1] << 8) | bm->map[bgrIndex];
        }
    }
}

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
void font_show(char *text,int pixelSize,int outFrameWidth,int outFrameHeight,int outFrameColor,int fontPosX,int fontPosY,int fontColor,int frameToLcdPosX,int frameToLcdPosY)
{
	//1.初始化字库 
    // 注意要先将ttf文件放入开发板上
    font *f = fontLoad("simfang.ttf"); // 指定字库文件，比如simfang.ttf

    //2.设置字体的大小 
    fontSetSize(f, pixelSize);

    //3.设置字体输出框的大小
    bitmap *bm;
    bm = createBitmapWithInit(outFrameWidth, outFrameHeight, 4, outFrameColor);

    //4.把字体输出到输出框中
    fontPrint(f, bm, fontPosX, fontPosY, text, fontColor, 0);

    //5.将bm妥善地放置到LCD上显示出来
    showbitmap(bm, frameToLcdPosX, frameToLcdPosY);

	// 关闭bitmap
	destroyBitmap(bm);
   
	// 关闭字体库
	fontUnload(f);
}