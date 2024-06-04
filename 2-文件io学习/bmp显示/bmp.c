#include "bmp.h"


int bmp_show(char *bmpFile, int posX, int posY)
{
    //2、打开图片文件
    int bmpFd = open(bmpFile, O_RDONLY);
    if(bmpFd == -1)
    {
        perror("open bmp error");
        return -1;
    }
    //读取文件头 14
    struct tagBITMAPFILEHEADER bfh;
    read(bmpFd, &bfh, sizeof(bfh));

    //读取文件信息头  40
    struct tagBITMAPINFOHEADER bih;
    read(bmpFd, &bih, sizeof(bih));

    //宽度字节数4的倍数判断
    if((bih.biWidth*3) %4 != 0)
    {
        printf("图片宽度不是4的倍数\n");
        close(bmpFd);
        return -1;
    }
    //printf("宽度:%d, 高度:%d, 位深:%d\n", bih.biWidth, bih.biHeight, bih.biBitCount);
    //printf("文件大小:%d\n", bih.biSizeImage+54);

    int width = bih.biWidth;
    int height = bih.biHeight;

    //3、读取图片颜色数据 
    char bmpbuf[width*height*3] ; //一共是800*480个像素点，每个像素点3个字节
    read(bmpFd, bmpbuf, sizeof(bmpbuf));

    //将图像中的每个像素点 BGR 转换为 ARGB
    int tempbuf[width*height];//存储转换之后的颜色数据
    for(int i=0,j=0; i<width*height; i++,j+=3)
    {
        tempbuf[i] =0x00<<24 | bmpbuf[j+2]<<16 |  bmpbuf[j+1]<<8 |  bmpbuf[j] ;
    }

    //将图片进行上下颠倒
    int lcdbuf[height][width];
    for(int j=0; j<height; j++)
    {
        for(int i=0; i<width; i++)
        {
            lcdbuf[j][i] = tempbuf[(height-1-j) * width + i];
        }
    }   
    //再将数据赋值到液晶屏的映射内存空间中
    for(int j=0; j<height; j++)
    {
        for(int i=0; i<width; i++)
        {
            lcd_p[j+posY][i+posX] = lcdbuf[j][i];
        }
    }
    //6、关闭图片文件
    close(bmpFd);
}