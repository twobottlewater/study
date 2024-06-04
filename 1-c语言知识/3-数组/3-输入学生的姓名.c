#include<stdio.h>

int main()
{
#if 0
    //获取三个同学的姓名
    //"zhang3"  "li4" "wang5"   
    char name1[256] = {0};
    char name2[256] = {0};
    char name3[256] = {0};

    printf("请输入第1个同学的姓名:");
    //scanf("%s",&name1); // 你们的写法，一定会有同学写成这样的，错误的    因为数组的名字本身就是代表地址了
    scanf("%s",name1);

    printf("请输入第2个同学的姓名:");
    scanf("%s",name2);
    
    printf("请输入第3个同学的姓名:");
    scanf("%s",name3);

    printf("%s  %s  %s \n",name1,name2,name3);
#endif 
    //使用二维数组存储多个同学的信息
    char name[60][256] = {0};
    int cnt=0;//学生的数量

    while(1){
        int cmd;
        printf("[1]新增学生 [2]显示数据:");
        scanf("%d",&cmd);

        switch (cmd)
        {
        case 1:
            /* code */
            {
                printf("请输入学生的姓名:");
                scanf("%s",name[cnt++]); //等价于&name[0][0]
                //cnt++;
            }
            break;
        case 2:
            /* code */
            for(int i=0; i<cnt; i++)
            {
                printf("%s\n",name[i]);
            }
            break;        
        default:
            break;
        }
    }



	return 0;
}