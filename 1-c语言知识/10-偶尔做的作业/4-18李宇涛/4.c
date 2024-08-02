/*将一个字符串倒序 "abcd" --->"dcba"*/

#include <stdio.h>
#include <string.h>



int main() {
    char str[] = "abcd";
	int length = strlen(str);
    int left = 0;
    int right = length - 1;
    printf("原始字符串: %s\n", str);
	while (left < right)
	{
	// 交换首尾字符
	char temp = str[left];
	str[left] = str[right];
	str[right] = temp;
	// 移动指针
	left++;
	right--;
	}
   
    printf("倒序后的字符串: %s\n", str);
    
    return 0;
}

