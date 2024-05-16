#include "game_charge.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "main.h"

extern GameUserInfo_t arr[100];
extern int userCnt;
extern int currentUser;  

void game_charge()
{

    int select = 0;
start:

    printf("[1]提升VIP等级 [2]购买资源礼包:");
    scanf("%d", &select);

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
int charge_vip()
{
    // 设置用户充钱的引导话术
    char *buf[] = {
        "冲一冲就是人生赢家，从此平步青云，一流高手",
        "想要成功，先充值",
        "只要99，就能报装备"};

    unsigned int money = 0;
again:
    printf("请输入充值金额:"); // 100
    scanf("%d", &money);

    // 先判断你当前的vip等级
    // 比如说你当前 vip是0  ，冲 6块钱   vip1
    // vip1  冲 36  才能提升 vip2
    // vip2 ---66  才能提升 vip3
    // vip3 ---96
    // 算法  vip*30+6

    while (1)
    {
        money -= arr[currentUser].vip * 30 + 6;
        arr[currentUser].vip++;

        // 剩余的钱 不够 冲 下一级
        int nextVipMoney = (arr[currentUser].vip + 1) * 30 + 6;
        if (money < nextVipMoney)
        {
            printf("亲，只要再冲%d 就能提升到高贵的VIP%d\n", nextVipMoney - money, arr[currentUser].vip + 1);
            printf("再充钱请按[1] 退出请按[2]:");
            int select = 0;
            scanf("%d", &select);
            if (select == 1)
            {
                goto again;
            }
            else if (select == 2)
            {
                printf("你真的要退出么...\n");
                int i = 0;
                while (1)
                {
                    printf("%s\n", buf[i]);
                    sleep(1);

                    if (i == 2)
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
    int mode = 0;
    scanf("%d", &mode);

    switch (mode)
    {
    case 1:
        /* code */
        arr[currentUser].res.wood += 100000;
        arr[currentUser].res.masonry += 100000;
        arr[currentUser].res.iron += 100000;
        break;
    case 2:
        /* code */
        arr[currentUser].res.wood += 1000000;
        arr[currentUser].res.masonry += 1000000;
        arr[currentUser].res.iron += 1000000;
        break;
    case 3:
        /* code */
        arr[currentUser].res.wood += 100000000;
        arr[currentUser].res.masonry += 100000000;
        arr[currentUser].res.iron += 100000000;
        break;
    default:
        break;
    }
}