#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
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

//资源结构体
struct Rource{
    unsigned long wood;//木材
    unsigned long masonry;//砖石
    unsigned long iron; //铁块
};

//设计一种数据类型 ，存储玩家信息
typedef struct {
    char account[20];
    char passwd[10];
    int id;
    int cityGrade; //城池等级
    int vip;
    struct Rource res;//资源
}GameUserInfo_t;

GameUserInfo_t arr[100] = {0};
int userCnt=0;
int currentUser = 0;  //记录当前登录的用户  记录的是数组下标

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

int charge_vip()
{
    //设置用户充钱的引导话术
    char *buf[] = {
        "冲一冲就是人生赢家，从此平步青云，一流高手",
        "想要成功，先充值",
        "只要99，就能报装备"
    };

    unsigned int money=0;
again:
    printf("请输入充值金额:");  //100
    scanf("%d",&money);

    //先判断你当前的vip等级
    //比如说你当前 vip是0  ，冲 6块钱   vip1
    //vip1  冲 36  才能提升 vip2
    //vip2 ---66  才能提升 vip3
    //vip3 ---96
    //算法  vip*30+6
    
    while(1)
    {
        money -= arr[currentUser].vip*30+6;
        arr[currentUser].vip++;

        //剩余的钱 不够 冲 下一级 
        int nextVipMoney = (arr[currentUser].vip+1) *30+6;
        if(money < nextVipMoney){
            printf("亲，只要再冲%d 就能提升到高贵的VIP%d\n",nextVipMoney-money,arr[currentUser].vip+1);
            printf("再充钱请按[1] 退出请按[2]:");
            int select=0;
            scanf("%d",&select);
            if(select == 1)
            {
                goto again;
            }
            else if(select == 2)
            {
                printf("你真的要退出么...\n");
                int i=0;
                while(1){                   
                    printf("%s\n",buf[i]);
                    sleep(1);

                    if(i==2)
                        break;
                    
                    i++;
                }
                printf("穷逼...............\n");
                return 0;
            }
        }
    }
}

void charge_resource()
{
    printf("[1]套餐一(各10万) [2]套餐二(各100万) [3](各1000万):");
    int mode =0 ;
    scanf("%d",&mode);

    switch (mode)
    {
        case 1:
            /* code */
            arr[currentUser].res.wood +=100000;
            arr[currentUser].res.masonry +=100000;
            arr[currentUser].res.iron +=100000;
            break;
        case 2:
            /* code */
            arr[currentUser].res.wood +=1000000;
            arr[currentUser].res.masonry +=1000000;
            arr[currentUser].res.iron +=1000000;
            break;    
        case 3:
            /* code */
            arr[currentUser].res.wood +=100000000;
            arr[currentUser].res.masonry +=100000000;
            arr[currentUser].res.iron +=100000000;
            break;   
        default:
            break;
    }
}


void game_charge()
{

    int select = 0;
start:

    printf("[1]提升VIP等级 [2]购买资源礼包:");
    scanf("%d",&select);

    switch (select)
    {
        case 1:
            /* code */
            charge_vip();           
            break;
        case 2:
            /* code */
            charge_resource();
            break;    
        default:
            break;
    }
}

void game_city()
{
    //等级越高，要的资源越多 ，消耗的时间也越长
    //时间
    int time = arr[currentUser].cityGrade * 3;

    int nextGrade = arr[currentUser].cityGrade+1;

    //资源
    unsigned long wood = nextGrade * nextGrade * nextGrade*nextGrade * 10000;//木材
    unsigned long masonry = nextGrade * nextGrade *1000;//砖石
    unsigned long iron  = nextGrade* nextGrade *100; //铁块

    printf("需要的资源: 木材%d  砖石%d  铁矿%d\n",wood,masonry,iron);

    //判断资源是否充足
    if(arr[currentUser].res.wood < wood){
        printf("木材数量不够，还缺%d 升级失败....\n",wood-arr[currentUser].res.wood);
        return ;
    }
    if(arr[currentUser].res.masonry < masonry){
        printf("砖石数量不够，还缺%d 升级失败....\n",masonry-arr[currentUser].res.masonry);
        return ;
    }
    if(arr[currentUser].res.iron < iron){
        printf("铁块数量不够，还缺%d 升级失败....\n",iron-arr[currentUser].res.iron);
        return ;
    }

    //vip等级越高，时间越短
    if(arr[currentUser].vip > 1)
        time = time / arr[currentUser].vip; 

    while(time--){
        usleep(100000);  //微秒
        printf("正在升级中[%d] 从%d级别城池 升 %d级别......\n",time,arr[currentUser].cityGrade,arr[currentUser].cityGrade+1);
    }

    printf("升级成功\n");

    arr[currentUser].res.wood -= wood;
    arr[currentUser].res.masonry -= masonry;
    arr[currentUser].res.iron -= iron;

    arr[currentUser].cityGrade++;    

}

void game_show()
{
    printf("-----------个人信息------------------\n");
    char account[20];
    char passwd[10];
    int id;
    int cityGrade; //城池等级
    int vip;
    struct Rource res;//资源

    printf("用户名:%s\n",arr[currentUser].account);
    printf("游戏ID:%d\n",arr[currentUser].id);
    printf("城池等级:%d\n",arr[currentUser].cityGrade);
    printf("VIP:%d\n",arr[currentUser].vip);
    printf("木材:%d  砖石:%d  铁矿:%d\n",arr[currentUser].res.wood,arr[currentUser].res.masonry,arr[currentUser].res.iron);
}

void game_leifeng()
{
    printf("*\n");
    printf("\n");
 


}

int main()
{
    //设置随机数种子
    srand(time(NULL));
    bool loginFlag = false;

    while(1)
    {
        int mode = 0;
        printf("[1]注册  [2]登录  [3]退出:");
        scanf("%d",&mode);

        switch (mode)
        {
            case 1:
                /* code */
                game_register();
                break;
            case 2:
                /* code */
                if(game_login() == true){
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

        if(loginFlag == true)
            break;
    }

    //游戏界面
    while(1)
    {
        int mode =0;
        printf("[1]充钱  [2]提升城池等级  [3]对阵   [4]刷副本  [5]个人信息  [6]退出:");
        scanf("%d",&mode);

        switch (mode)
        {
            case 1:
                game_charge();
                break;
             case 2:
                game_city();
                break;  
             case 3:
                
                break;              
             case 4:
                game_leifeng();
                break;   
             case 5:
                game_show();
                break;   

            default:
                break;
        }
    }



    return 0;
}