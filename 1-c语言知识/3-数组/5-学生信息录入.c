#include<stdio.h>
#include <stdbool.h>
#include <string.h>

int main()
{
    /*
    3、设计一个程序，实现 学生信息录入系统（姓名、年龄、分数）

        1、可以制作一个简单的登录系统

            账号、密码的验证 （其实就是字符串的比较  strcmp）

        2、录入信息之后，可以查询
    */
    //姓名
    char name[60][256] = {0};
    //年龄
    int age[60];
    //分数
    float score[60];

    //账号
    char account[10] = {0};
    //密码
    char passwd[10] = {0};

    //记录错误的次数
    int cnt=3;
    int count =0 ;//学生的数量
    //登录
    while(1)
    {
        //1、让用户从键盘输入账号和密码
        printf("请输入账号:");
        scanf("%s",account);

        printf("请输入密码:");
        scanf("%s",passwd);

        //2、默认的账号 admin   密码 123   跟输入的进行比较 ，如果相同  则退出循环
        //账号
       // if(account[0] == 'a' && account[1] =='d' && account[2] == 'm' && account[3] =='i' && account[4] == 'n')
        if(strcmp(account,"admin") == 0)
        {
            if(strcmp(passwd,"123") == 0)//密码
            {
                printf("登录成功...............\n");
                break;
            }
            else{
                 printf("密码输入错误,请重新输入\n");

                memset(account,0,10);
                memset(passwd,0,10);

                cnt--;
                if(cnt==0)
                {
                    goto err;
                }
                continue;
            }
        }
        else{
            printf("账号输入错误,请重新输入\n");

            memset(account,0,10);
            memset(passwd,0,10);
        }



    }


    bool exitFlag=false;
    //主系统
    while(1)
    {
        int mode = -1;
        printf("[1]插入数据 [2]显示数据  [3]退出：");
        scanf("%d",&mode);

        switch (mode)
        {
            case 1:
                /* code */
                {
                    /*
                        //姓名
                        char name[60][256] = {0};
                        //年龄
                        int age[60];
                        //分数
                        float score[60];
                    */
                    printf("请输入姓名 年龄 分数:");
                    //scanf("%s",&name[count][0]);
                    //scanf("%s",*(name+count));
                    scanf("%s",name[count]);

                    scanf("%d", age+count); //scanf("%d", &age[count]);

                    scanf("%f", score+count);

                    count++;
                }
                break;
            case 2:
                /* code */
                for(int i=0; i<count; i++){
                    printf("%-10s %-10d %-10.f\n",*(name+i),age[i],score[i]);
                }
                break;   
            case 3:
                /* code */
                exitFlag = true;
                break;     
            default:
                break;
        }


        if(exitFlag==true)
            break;
    }

err:
	return 0;
}