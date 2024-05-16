#include"game_city.h"
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

void game_city()
{
    // 等级越高，要的资源越多 ，消耗的时间也越长
    // 时间
    int time = arr[currentUser].cityGrade * 3;

    int nextGrade = arr[currentUser].cityGrade + 1;

    // 资源
    unsigned long wood = nextGrade * nextGrade * nextGrade * nextGrade * 10000; // 木材
    unsigned long masonry = nextGrade * nextGrade * 1000;                       // 砖石
    unsigned long iron = nextGrade * nextGrade * 100;                           // 铁块

    printf("需要的资源: 木材%lu  砖石%lu 铁矿%lu\n", wood, masonry, iron);

    // 判断资源是否充足
    if (arr[currentUser].res.wood < wood)
    {
        printf("木材数量不够，还缺%lu 升级失败....\n", wood - arr[currentUser].res.wood);
        return;
    }
    if (arr[currentUser].res.masonry < masonry)
    {
        printf("砖石数量不够，还缺%lu 升级失败....\n", masonry - arr[currentUser].res.masonry);
        return;
    }
    if (arr[currentUser].res.iron < iron)
    {
        printf("铁块数量不够，还缺%lu 升级失败....\n", iron - arr[currentUser].res.iron);
        return;
    }

    // vip等级越高，时间越短
    if (arr[currentUser].vip > 1)
        time = time / arr[currentUser].vip;

    while (time--)
    {
        usleep(100000); // 微秒
        printf("正在升级中[%d] 从%d级别城池 升 %d级别......\n", time, arr[currentUser].cityGrade, arr[currentUser].cityGrade + 1);
    }

    printf("升级成功\n");

    arr[currentUser].res.wood -= wood;
    arr[currentUser].res.masonry -= masonry;
    arr[currentUser].res.iron -= iron;

    arr[currentUser].cityGrade++;
}