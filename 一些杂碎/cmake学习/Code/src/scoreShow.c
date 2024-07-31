#include "../inc/main.h"



void *scoreShow(void *arg)
{   
    event_num=0;//比赛的节数-1
    char *initEvents[5] = {
        "第一节",
        "第二节",
        "第三节",
        "第四节",
        "第四节"};
    
    //分数初值
    font_show("0",72,140,140,WHITE,50,40,RED,200,190);//左边分数
    font_show("0",72,140,140,WHITE,50,40,RED,460,190);//右边分数
    font_show(initEvents[event_num],40,120,70,WHITE,0,10,RED,340,210);//比赛节数
    font_show("撤分",40,100,60,RED,0,10,WHITE,200,340);//左边撤销分数的按钮
    font_show("撤分",40,100,60,RED,0,10,WHITE,500,340);//右边撤销分数的按钮
    while (event_num!=5)
    {
        int x,y;
        touch_wait( &x, &y);
        //左队加分逻辑
        if(x>=200&&x<=340&&y>=190&&y<=330)
        {
            scoreL++;
            char score1[128]={0};
            sprintf(score1,"%d",scoreL);
            font_show(score1,72,140,140,WHITE,50,40,RED,200,190);//左边分数

        }
        //左边撤销分数逻辑
        else if(x>=200&&x<=300 && y>=340&&y<=400)
        {
            scoreL--;
            char score1[128]={0};
            sprintf(score1,"%d",scoreL);
            font_show(score1,72,140,140,WHITE,50,40,RED,200,190);//左边分数
        }
        //右队加分逻辑
        else if(x>=460&&x<=600&&y>=190&&y<=330)
        {
            scoreR++;
            char score2[128]={0};
            sprintf(score2,"%d",scoreR);
            font_show(score2,72,140,140,WHITE,50,40,RED,460,190);//右边分数
        }
        //右边撤销分数逻辑
        else if(x>=500&&x<=600 && y>=340&&y<=400)
        {
            scoreR--;
            char score2[128]={0};
            sprintf(score2,"%d",scoreR);
            font_show(score2,72,140,140,WHITE,50,40,RED,460,190);//右边分数
        }
        //切换节数逻辑
        else if(x>=340&&x<=460&&y>=210&&y<=280)
        {
            event_num++;
            foulClear();
            attack_seconds=24;
            char Events[128]={0};
            //把数组里面的元素加进来
            sprintf(Events,"%s",initEvents[event_num]);
            font_show(Events,40,120,70,WHITE,0,10,RED,340,210);//中间场次
            if(event_num>3)
            {
                suspend_flag=1;
                break;
            }
            seconds =600; 
        }
        //暂停时间的逻辑 
        else if(x>=305 &&x<=495 && y>=330&&y<=410)
        {
            suspend_flag=!suspend_flag;
            //  attack_seconds=24;
        }
        //技术台改篮板球进攻时间
        else if(x>=0&&x<=(180)&&y>=0&&y<=(410))
        {
            attack_seconds=24;
        }
        else if (x>=620&&x<=(799)&&y>=0&&y<=(410))
        {
            attack_seconds=14;
        }

    }


}

//犯规清零
void foulClear()//犯规清零
{
    foulL=0;
    foulR=0;
    char foul[128]={"犯规："};
    char foul_show[128]={0};
    sprintf(foul_show,"%s%d",foul,foulL);
    font_show(foul_show,30,140,45,WHITE,0,10,BLACK,200,145);//左边犯规按钮
    sprintf(foul_show,"%s%d",foul,foulR);
    font_show(foul_show,30,140,45,WHITE,0,10,BLACK,460,145);//右边犯规按钮
}

void *foulShow(void *arg)
{
    foulClear();
    char foul[128]={"犯规："};
    char foul_show[128]={0};

    while (1)
    {
        int x,y;
        touch_wait( &x, &y);
        //左队犯规逻辑
        if(x>=190&&x<=(190+160)&&y>=130&&y<=(130+60))
        {
            foulL++;
            sprintf(foul_show,"%s%d",foul,foulL);

            if(foulL>4)
            {
                font_show(foul_show,30,140,45,RED,0,10,BLACK,200,145);//左边犯规超4次就红了
            }
            else
            {
                font_show(foul_show,30,140,45,WHITE,0,10,BLACK,200,145);//左边犯规按钮
            }
        }
         //右队犯规逻辑
        if(x>=460&&x<=(460+160)&&y>=130&&y<=(130+60))
        {
            foulR++;
            sprintf(foul_show,"%s%d",foul,foulR);

            if(foulR>4)
            {
                font_show(foul_show,30,140,45,RED,0,10,BLACK,460,145);//右边犯规超4次就红了
            }
            else
            {
                font_show(foul_show,30,140,45,WHITE,0,10,BLACK,460,145);//右边犯规按钮
            }
        }
    }
    

}