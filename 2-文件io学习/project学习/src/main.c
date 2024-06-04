#include <stdio.h>

#include "touch.h"
#include "lcd.h"
#include "bmp.h"
#include "log.h"
#include "dir.h"


int main()
{
    //初始化日志系统
    log_init();
    //液晶屏初始化
    lcd_init();
    //res目录中初始化图片
    List_t*list = dir_searchToList("./res", ".bmp");

    

    while (1)
    {
        int x, y;
        int mode = -1;
        touch_wait(&x,&y);

        if(x>=0 && x<800/2)
            mode = 1;
        else if(x>=800/2 && x<800)
            mode = 2;

        switch (expression)
        {
            case 1:
                {
                    bmp_show(list, 0,0);
                }
                break;
            case 2:
                {

                }
                break;        
            default:
                break;
        }
    }
    
    lcd_destory();
    log_destory();

    return 0;
}