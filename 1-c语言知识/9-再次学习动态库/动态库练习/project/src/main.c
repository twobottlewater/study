#include <stdio.h>

#include "touch.h"
#include "lcd.h"
#include "bmp.h"
#include "log.h"
#include "dir.h"
#include "mfont.h"

#include <pthread.h>

//线程的函数 函数的返回值一定是void*  参数一定是void*
void*Timeroutine(void*arg)
{
	while(1)
	{
		time_t tm = time(NULL);
		struct tm *lTime = localtime(&tm);

		printf("date:%d:%d:%d\n",
						(1900+lTime->tm_year),
						(1+lTime->tm_mon),
						lTime->tm_mday);

		printf("time:%d:%d:%d\n",
						lTime->tm_hour,
						lTime->tm_min,
						lTime->tm_sec);
		
		char tbuf[1024]={0};
		sprintf(tbuf,"%d:%d:%d",lTime->tm_hour,lTime->tm_min,lTime->tm_sec);
		//调用字库显示时间
		font_show(tbuf,24,150,80,0x00ffffff,0,0,0x00000000,640,0);
		
		
		sleep(1);
		

	}
}

//arm-linux-gcc ./src/*.c  -o  project   -I ./inc/   -lpthread  -lm  


int main()
{
    //初始化日志系统
    log_init();
    //液晶屏初始化
    lcd_init();

	//创建一条子线程，执行时间的循环显示
	pthread_t thread;
    pthread_create(&thread,NULL,Timeroutine,NULL);


    //res目录中初始化图片
    DNode_t*list = dir_searchToList("./res", ".bmp");

    DNode_t*p = list->next;

    while (1)
    {
        int x, y;
        int mode = -1;
        touch_wait(&x,&y);

        if(x>=0 && x<800/2)
            mode = 1;
        else if(x>=800/2 && x<800)
            mode = 2;

        switch (mode)
        {
            case 1:
                {
                    p = p->prev;
                    bmp_show(p->data.fileName, 0,0);
                }
                break;
            case 2:
                {
                    p = p->next;
                    bmp_show(p->data.fileName, 0,0);
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