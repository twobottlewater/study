#include "../inc/main.h"




// 线程函数实现
void *countdown(void *arg)
 {
    seconds =600; 
    suspend_flag=0;
    attack_seconds=24;
    int minute = 0;
    int minute_seconds =0;
    char buf[20];
    
    while (seconds>=0) 
    {
        minute=seconds/60;
        minute_seconds=seconds%60;
        char Arrymins[256] = {0};

        sprintf(Arrymins,"%02d:%02d",(char*)minute,(char*)minute_seconds);
        font_show(Arrymins,72,190,80,WHITE,5,5,RED,305,330);//倒计时


        if(attack_seconds<=0)
        {
         //这个是如果24秒违例就暂停
          suspend_flag = 1;
          attack_seconds=24;
        }
        if (seconds > 0 && suspend_flag == 0)
        {  
            sleep(1); // 暂停1秒  
            seconds--;//总时间减一
            attack_seconds--;//24秒进攻时间减一
        }
        //一节比赛结束就下一节
        if (seconds<=0)
        {
            event_num++;
            foulClear();//犯规清零
            seconds =600; 
            foulL=0;
            foulR=0;
        }



        //展示24秒进攻时间
        if (attack_seconds<16)
        {
            /* code */
            sprintf(buf,"%d",attack_seconds);
            font_show(buf,40,60,80,RED,15,10,WHITE,360,80);
        }
        else
        {
            sprintf(buf,"%d",attack_seconds);
            font_show(buf,40,60,80,WHITE,15,20,RED,360,80);
        }
        
    
    }
    return NULL;
}

