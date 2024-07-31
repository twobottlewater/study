#include "../inc/main.h"


//左队队友信息显示
void PlayerInformationL()
{
    FILE* fp = fopen("./res/player_left.txt","rb+");
    if(fp == NULL)
    {
        printf("fopen info.txt error\n");
    }
    int i=0;
    int j=0;
    while(i!=12)
    {
        int id;
        char name[256]={0};
        char idName1[256];
        //以指定的格式从文本fp中获取数据，存储到变量对应的内存空间上
        fscanf(fp,"%d %s",&id,name);
        sprintf(idName1,"%d %s",id,name);
        font_show(idName1,28,180,34,WHITE,3,3,BLACK,0,0+j);
        i++;
        j=j+34;
    }
    fclose(fp);

}


//右队队友信息显示
void PlayerInformationR()
{
    FILE* fd = fopen("./res/player_right.txt","rb+");
    if(fd == NULL)
    {
        perror("fopen info.txt error\n");
    }
    int i=0;
    int j=0;
    while(i!=12)
    {
        int id;
        char name[256]={0};
        char idName1[256];
        //以指定的格式从文本fp中获取数据，存储到变量对应的内存空间上
        fscanf(fd,"%d %s",&id,name);
        sprintf(idName1,"%d %s",id,name);
        font_show(idName1,28,180,34,WHITE,3,3,BLACK,620,j);
        i++;
        j=j+34;
    }
    fclose(fd);

}

//比赛标题
void GameName()
{
    FILE* fp = fopen("./res/game_name.txt","rb+");
    if(fp == NULL)
    {
        printf("fopen info.txt error\n");
    }

    int id;
    char name1[256]={0};
    char idName3[256];
    //以指定的格式从文本fp中获取数据，存储到变量对应的内存空间上
    fscanf(fp,"%d %s",&id,name1);
    sprintf(idName3,"%d %s",id,name1);
    font_show(idName3,45,400,80,WHITE,20,15,BLACK,200,0);

    fclose(fp);
}


//队伍名字
void teamNameLeft()
{
    FILE* fp = fopen("./res/left_team_name.txt","rb+");
    if(fp == NULL)
    {
        printf("fopen left_team_name.txt error\n");
    }
    char name2[256]={0};
    //以指定的格式从文本fp中获取数据，存储到变量对应的内存空间上
    fscanf(fp,"%s",name2);
    font_show(name2,40,200,60,WHITE,0,10,BLUE,200,80);

    fclose(fp);
}

void teamNameRight()
{
    FILE* fp = fopen("./res/right_team_name.txt","rb+");
    if(fp == NULL)
    {
        printf("fopen right_team_name.txt error\n");
    }
    char name3[256]={0};
    //以指定的格式从文本fp中获取数据，存储到变量对应的内存空间上
    fscanf(fp,"%s",name3);
    font_show(name3,40,200,60,WHITE,45,10,BLUE,400,80);

    fclose(fp);
}