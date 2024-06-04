#include <stdio.h>

#include "bmp.h"

int main()
{
    lcd_init();

    int x=0;

    while (1)
    {
        bmp_show("white.bmp",0,0);
        bmp_show("love.bmp",x,100);

        x = (x+100) % 600;

        // 延时
        sleep(1);
    }
    
    

    lcd_destory();
}