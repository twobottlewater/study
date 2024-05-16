#include <stdio.h>
#include <ctype.h>
#include <string.h>
int main() {
  char name[5][20];
  int i, j;

  // 从键盘输入5个名字
  for (i = 0; i < 5; i++) {
    printf("请输入第%d个人的名字：", i + 1);
    scanf("%s", name[i]);
  }

  // 判断每个名字是否符合要求
  for (i = 0; i < 5; i++) {
    // 判断名字长度
    if (strlen(name[i]) > 8) {
      printf("第%d个人的名字长度超过8个字符，不符合要求\n", i + 1);
      continue;
    }

    // 判断是否包含小写字母
    int has_lower = 0;
    for (j = 0; j < strlen(name[i]); j++) {
      if (islower(name[i][j])) {
        has_lower = 1;
        break;
      }
    }
    if (!has_lower) {
      printf("第%d个人的名字缺少小写字母\n", i + 1);
      continue;
    }

    // 判断是否包含大写字母
    int has_upper = 0;
    for (j = 0; j < strlen(name[i]); j++) {
      if (isupper(name[i][j])) {
        has_upper = 1;
        break;
      }
    }
    if (!has_upper) {
      printf("第%d个人的名字缺少大写字母\n", i + 1);
      continue;
    }

    // 判断是否包含数字字符
    int has_digit = 0;
    for (j = 0; j < strlen(name[i]); j++) {
      if (isdigit(name[i][j])) {
        has_digit = 1;
        break;
      }
    }
    if (!has_digit) {
      printf("第%d个人的名字缺少数字字符\n", i + 1);
      continue;
    }

    // 符合要求，打印名字
    printf("第%d个人的名字符合要求：%s\n", i + 1, name[i]);
  }

  return 0;
}
