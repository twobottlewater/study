#ifndef _MAIN_H
#define  _MAIN_H


#include "../inc/lcd.h"
#include "../inc/bmp.h"
#include "../inc/font.h"
#include <pthread.h>
#include "../inc/mfont.h"
#include "../inc/touch.h"


int seconds ;//剩余秒数
int suspend_flag;//暂停时间标志位
int event_num;//比赛节数
int  attack_seconds;

int scoreL;//左队分数
int scoreR;//右对分数

int foulL;//左队犯规次数
int foulR;//右队犯规次数
int foul_flag;
//记时的函数
void *countdown(void *arg);
void *attck_time(void *arg);//这个是进攻时间

//广告展示函数
void *ad_gif_show(void *arg);


//展示分数和节数的函数
void *scoreShow(void *arg);
//展示犯规数的函数
void *foulShow(void *arg);
//犯规数清零
void foulClear();

//比赛队伍信息
void GameName();
void teamNameLeft();
void teamNameRight();
//展示左边队友信息
void PlayerInformationL();
//展示右边队友信息
void PlayerInformationR();
#endif