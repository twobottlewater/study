#include "main.h"


#include "game_solo.h"

// 全局变量的定义
GameUserInfo_t arr[100] = {0};
int userCnt = 0;
int currentUser = 0; // 记录当前登录的用户  记录的是数组下标

extern void game_register();
extern bool game_login();
extern void game_charge();
extern void game_city();
extern void game_leifeng();
extern void game_show();
  
int main()
{
    // 设置随机数种子
    srand(time(NULL));
    bool loginFlag = false;

    while (1)
    {
        int mode = 0;
        printf("[1]注册  [2]登录  [3]退出:");
        scanf("%d", &mode);

        switch (mode)
        {
        case 1:
            /* code */
            game_register();
            break;
        case 2:
            /* code */
            if (game_login() == true)
            {
                printf("---------------登录成功----------------\n");
                loginFlag = true;
            }
            break;
        case 3:
            /* code */
            return 0;
            break;
        default:
            break;
        }

        if (loginFlag == true)
            break;
    }

    // 游戏界面
    while (1)
    {
        int mode = 0;
        printf("[1]充钱  [2]提升城池等级  [3]对阵   [4]刷副本  [5]个人信息  [6]退出:");
        scanf("%d", &mode);

        switch (mode)
        {
        case Cmd_Mode_Charge:
            game_charge();
            break;
        case Cmd_Mode_City:
            game_city();
            break;
        case Cmd_Mode_Facing:
            game_solo();
            break;
        case Cmd_Mode_Leifeng:
            game_leifeng();
            break;
        case Cmd_Mode_ShowInfo:
            game_show();
            break;
        case Cmd_Mode_Exit:
            return 0;
            break;
        default:
            break;
        }
    }

    return 0;
}