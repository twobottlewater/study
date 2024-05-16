#include <stdio.h>

// 函数声明
int stringLength(const char *str);

int main() {
    char myString[62]={0};
    printf("请输入一个一个字符串\n");
    int i=0;
    char c;
    //scanf("%s",myString);
    //fgets(myString, sizeof(myString), stdin);//读多了一个\n
   // myString[strcspn(myString, "\n")] = 0;  // 查找换行符并替换为结束符 '\0'
   while((c=getchar())!='\n')
   {
    myString[i]=c;
    i++;
   }
    myString[i] = '\0'; 
    printf("字符串'%s'的长度 is %d.\n",myString,stringLength(myString));
    return 0;
}

// 函数定义
int stringLength(const char *str) {
    int count = 0;  // 初始化计数器
    while (*str != '\0') {  // 循环直到字符串结束符 '\0'
        count++;  // 为每个字符递增计数器
        str++;  // 移动到下一个字符
    }
    return count;  // 返回字符总数
}

