/*1、编写一个程序，该程序读取输入直到遇到#字符，然后报告读取的空格数目、读取的换行符数目以及读取的所有其他字符数目。
例如：输入:a 3 b
          c%#
      输出:spaces = 2, lines = 1, characters= 5
答：*/
#include <stdio.h>   
#include <ctype.h>

int main() {
    int spaces = 0;
    int lines = 0;
    int other_chars = 0;
    int current_char;

    while ((current_char = getchar()) != EOF) {
        if (current_char == '#') {
            break;
        }
/*	 C 语言中，getchar() 函数从标准输入（通常是键盘）读取下一个字符。EOF 是一个宏，
表示 “end of file”，即文件结束。在标准输入的情况下，EOF 通常在用户按下文件结束符时产生，
这个符号在大多数环境中可以通过按下 Ctrl+D（在 Unix/Linux 系统中）或者 Ctrl+Z（在 Windows 系统中）来生成。while ((current_char = getchar()) != EOF) 这行代码是一个 while 循环的条件表达式，它的作用是：调用 getchar() 函数读取一个字符。读取的字符赋值给变量 current_char。检查 current_char 是否不等于 EOF。如果 current_char 不等于 EOF，则循环继续；如果等于 EOF，则循环结束。*/
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

