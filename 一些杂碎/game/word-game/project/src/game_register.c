#include"game_register.h"
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

void game_register()
{
    printf("请注册账号:");
    scanf("%s",arr[userCnt].account);

loop:
    printf("请注册密码:");
    scanf("%s",arr[userCnt].passwd);

    if(strlen(arr[userCnt].passwd) >10){
        printf("密码长度过长，请重新输入.....\n");
        goto loop;
    }

    //随机一个玩家ID
    arr[userCnt].id =  rand() % 100000;

    //城池等级
    arr[userCnt].cityGrade = 1;

    //vip
    arr[userCnt].vip = 0;

    //资源
    arr[userCnt].res.wood = 10000;
    arr[userCnt].res.masonry = 10000;
    arr[userCnt].res.iron = 10000;


    userCnt++;
}