#include<stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
/*
2、输入一个字符串ch，并做以下更改后输出： 
1：如果里面有a或者A ，都输出*；
2：如果里面有b或者B ，都输出#；
其它的数据保持不变。如果输入的是字符串第一个字符ch[0]是x， 则退出程序
*/
    char*buf = malloc(100);
    
    while(1)
    {
        memset(buf,0,100);
        printf("请输入字符串:");
        scanf("%s",buf);

        //如果输入的是字符串第一个字符ch[0]是x
        if(buf[0] == 'x')
            break;

        //如果里面有a或者A ，都输出*；
        char*p = buf;
        while(1)
        {
            if(*p == 'a' ||  *p == 'A')
            {
                *p = '*';
            }
            //如果里面有b或者B ，都输出#；
            else if(*p == 'b' ||  *p == 'B')
            {
                *p = '#';
            }  

            //p++;   

            if(*(++p) == '\0')
                break;      
        }

        printf("%s\n",buf);
    }


    free(buf);

	return 0;
}