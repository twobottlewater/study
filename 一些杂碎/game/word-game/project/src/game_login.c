#include "game_login.h"
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

bool game_login()
{
    char account[20] = {0};
    char passwd[10] = {0};
    int passwdErrCnt = 3;

    printf("请登录账号:");
    scanf("%s",account);

passwdErr:
    printf("请登录密码:");
    scanf("%s",passwd);

    bool ret=false;

    //对比
    for(int i=0; i<userCnt; i++){
        //先比较账号
        if(strcmp(arr[i].account,account) == 0){
            //再比较密码
            if(strcmp(arr[i].passwd,passwd) == 0){
                //登录成功
                ret = true;
                currentUser = i;
                break;
            }
            else{
                printf("密码错误，请重新输入,你还有%d次机会......\n",passwdErrCnt--);
                memset(passwd,0,sizeof(passwd));
                if(passwdErrCnt>0)
                    goto passwdErr;
            }
        }
    }

    return ret;
}