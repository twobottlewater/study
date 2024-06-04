#include <stdio.h>
#include <string.h>

/*通过键盘输入3名学生4门课程的成绩，
分别求每个学生的平均成绩和每门课程的平均成绩。
要求所有成绩均放入一个4行5列的数组中，输入时同一人数据间用空格,不同人用回车 
其中最后一列和最后一行分别放每个学生的平均成绩、每门课程的平均成绩及班级总平均分*/

int main()
{
  int scores[3][5] = {0};
  int i, j;
  float avg_stu[3], avg_sub[4];
  float sum_stu[3] = {0}, sum_sub = 0;

  // 输入成绩
  for (i = 0; i < 3; i++) {
     printf("开始输入第%d个同学的成绩",i+1);
    for (j = 0; j < 4; j++) {
      printf("请输入第%d门课程的成绩\n",j+1);
      scanf("%d", &scores[i][j]);
      
    }
   
  }

  // 计算每个学生的平均成绩
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      sum_stu[i] += scores[i][j];
    }
    avg_stu[i] = sum_stu[i] / 3;
  }

  // 计算每门课程的平均成绩
  for (j = 0; j < 4; j++) {
    for (i = 0; i < 3; i++) {
      sum_sub += scores[i][j];
    }
    avg_sub[j] = sum_sub / 3;
  }

  // 输出成绩
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 5; j++) {
      printf("%d ", scores[i][j]);
    }
    printf("\n");
  }

  // 输出平均成绩
  for (i = 0; i < 3; i++) {
    printf("学生%d平均成绩: %.2f\n", i + 1, avg_stu[i]);
  }
  for (j = 0; j < 4; j++) {
    printf("第%d门课平均成绩: %.2f\n", j + 1, avg_sub[j]);
  }
  printf("班级总平均分: %.2f\n", sum_sub / 12);

  return 0;
}
