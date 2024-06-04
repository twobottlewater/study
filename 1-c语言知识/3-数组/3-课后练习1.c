#include<stdio.h>
#include <stdbool.h>

int main()
{
    /*
    1、定义一个二维数组，存入 5 个学生的数学、语文、英语、物理、化学 5 门课程的成绩，
    计算并输出每一门课程的平均成绩和每一位学生的平均成绩。
    */
    //第1个5表示5个同学  第二个5表示 每个同学5门课程
               //      j=0   j=1  j=2 j=3  j=4
               //       数学 语文 英语 物理 化学
    int array[5][5] = {{100 ,60  ,60 ,70  ,80}, //第1个同学   i=0
                       {100 ,78  ,78 ,70  ,80}, //第2个同学   i=1
                       {89  ,45  ,78 ,70  ,90}, //第3个同学   i=2
                       {89  ,45  ,78 ,70  ,90}, //第4个同学   i=3
                       {67  ,45  ,78 ,90  ,20}}; //第5个同学  i=4

    float score = 0;

    for(int k=0;k<5; k++) //5门课程
    {
        score = 0;
        //k==0 算的是数学  k==1 语文
        for(int i=0; i<5; i++)
        {
            score += array[i][k];
        }

        printf("%f\t",score / 5);
    }
    
    //每个学生的平均成绩
    //第1个同学
    //score = array[0][0] +   array[0][1] +   array[0][2] +   array[0][3] +   array[0][4];
    printf("\n");
    for(int k=0;  k<5; k++)
    {
        score=0;

        for(int i=0; i<5; i++)
        {
            score +=  array[k][i];
        }

        printf("第%d同学:%.1f\n",k+1,score/5);
    }

	return 0;
}