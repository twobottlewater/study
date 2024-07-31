#include "../inc/main.h"


void *ad_gif_show(void *arg)
{
    int adv[50][1];
    while(1)
    {
        for(int i=0;i<799;i++)
        {
            for(int j=410;j<479;j++)
            {
                if(i==0)
                {
                    //不断地把后面一列的x坐标的背景颜色赋值给adv[][]
                    adv[j][0] = lcd_p[j][i];
                    
                }
                lcd_p[j][i] = lcd_p[j][i+1];
            }
        }
        for(int j=410;j<479;j++)
        {
            lcd_p[j][799] = adv[j][0];
        }
    }

}