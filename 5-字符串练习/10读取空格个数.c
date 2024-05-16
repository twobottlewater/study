#include <stdio.h>   
#include <ctype.h>
/*
1、编写一个程序，该程序读取输入直到遇到#字符，然后报告读取的空格数目、读取的换行符数目以及读取的所有其他字符数目。
例如：输入:a 3 b
          c%#
      输出:spaces = 2, lines = 1, characters= 5*/
int main() {
    int spaces = 0;
    int lines = 0;
    int other_chars = 0;
    int current_char;

    while ((current_char = getchar()) != EOF) {
        if (current_char == '#') {
            break;
        }
        /*
        函数原型定义在 <ctype.h> 头文件中，其原型如下：
        c
        复制
        int isspace(int c);
        如果 c 是空白字符，isspace 函数将返回非零值（通常是 1）；如果不是空白字符，则返回 0。
        */
        if (isspace(current_char)) {
            if (current_char == ' ') {
                spaces++;
            } else if (current_char == '\n') {
                lines++;
            }
        } else {
            other_chars++;
        }
    }

    printf("spaces = %d, lines = %d, characters = %d\n", spaces, lines, other_chars);

    return 0;
}