#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0
1、编写一个程序，该程序读取输入直到遇到#字符，
然后报告读取的空格数目、读取的换行符数目以及读取的所有其他字符数目。
例如：输入:a 3 b
          c%#
      输出:spaces = 2, lines = 1, characters= 5
#endif 

int main()
{
    char str[100] = {0};
    int cnt=0;
    int arr[3] = {0}; //arr[0]空格数量  arr[1]存读取的换行符数目  arr[2]其它字符
    while(1)
    {
        scanf("%c",&str[cnt]); // str[cnt] = getchar();

        if(str[cnt] == '#')
            break;
        cnt++;
    }

    for(int i=0; i<cnt; i++)
    {
        if(str[i] == ' ')
        {
            arr[0]++;
        }
        else if(str[i] == '\n')
        {
            arr[1]++;
        }
        else{
            arr[2]++;
        }
    }

    printf("空格%d 换行%d 其它%d\n",arr[0],arr[1],arr[2]);

	return 0;
}