#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "game_show.h"
#include "game_charge.h"
#include "game_city.h"
#include "game_leifeng.h"
#include "game_login.h"
#include "game_register.h"
/*
设计一个简单的文字战争策略游戏
游戏账号  密码  ID  城池等级   vip贵族等级  资源（木材数量  砖石数量 铁块数量）

功能：
1、注册账号
2、登录
3、每个玩家初始资源  城池等级=1  vip=1  木材  砖石  铁矿  各 1万
4、刷雷峰塔副本，获取资源（每提升一层，获取的资源越多  使用算法实现）
5、城池升级 ，每次提升一级 消耗的资源 成倍数提升
*/

// 资源结构体
struct Rource
{
    unsigned long wood;    // 木材
    unsigned long masonry; // 砖石
    unsigned long iron;    // 铁块
};

// 设计一种数据类型 ，存储玩家信息
typedef struct
{
    char account[20];
    char passwd[10];
    int id;
    int cityGrade; // 城池等级
    int vip;
    struct Rource res; // 资源
} GameUserInfo_t;

enum CmdMode
{
    Cmd_Mode_Charge = 1,
    Cmd_Mode_City,
    Cmd_Mode_Facing,
    Cmd_Mode_Leifeng,
    Cmd_Mode_ShowInfo,
    Cmd_Mode_Exit
};
GameUserInfo_t arr[100];
int userCnt;
int currentUser;  



