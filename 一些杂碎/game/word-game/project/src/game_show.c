#include"game_show.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include"main.h"

extern GameUserInfo_t arr[100];
extern int userCnt;
extern int currentUser;  

void game_show()
{
    printf("-----------个人信息------------------\n");
    char account[20];
    char passwd[10];
    int id;
    int cityGrade; // 城池等级
    int vip;
    struct Rource res; // 资源

    printf("用户名:%s\n", arr[currentUser].account);
    printf("游戏ID:%d\n", arr[currentUser].id);
    printf("城池等级:%d\n", arr[currentUser].cityGrade);
    printf("VIP:%d\n", arr[currentUser].vip);
    printf("木材:%lu  砖石:%lu  铁矿:%lu\n", arr[currentUser].res.wood, arr[currentUser].res.masonry, arr[currentUser].res.iron);
}