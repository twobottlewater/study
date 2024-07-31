#include "../inc/main.h"




int main()
{
    //液晶屏初始化
    lcd_init();
    //屏幕清屏
    lcd_draw_white_bg();
    bmp_show("./res/adpicture.bmp",0,410);
    PlayerInformationL();
    PlayerInformationR();
    GameName();
    teamNameLeft();
    teamNameRight();
    //创建一条子线程，执行广告的循环显示
	pthread_t adshowThread;
    pthread_create(&adshowThread,NULL,ad_gif_show,NULL);
    //创建一条子线程，执行时间的循环显示
    pthread_t timeThread;
    pthread_create(&timeThread,NULL,countdown,NULL);
    //创建一条子线程，执行分数的循环显示
	pthread_t scoreThread;
    pthread_create(&scoreThread,NULL,scoreShow,NULL);
    //创建一条子线程，执行犯规的循环显示
	pthread_t foul_show_Thread;
    pthread_create(&foul_show_Thread,NULL,foulShow,NULL);


    while (1)
    {
        /* code */
    }
    
    lcd_destory();


    return 0;
}