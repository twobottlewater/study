#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0
3、编写一个程序，清除用户输入字符串中的空格符并将之输出。（例如用户输入”a b”，输出”ab”）
#endif 

int main()
{   
    char buf[1024] ;
    memset(buf,0,1024);
    int i=0;

    while(1)
    {
        scanf("%c",buf+i);  //buf[i] = getchar();

        // if(*(buf+i) == '\n')
        //     break;

        // i++;
        if(buf[i++] == '\n')
            break;
    }

    printf("buf:%s\n",buf);

    char temp[1024] = {0};
    int j=0;
    char *p = buf;

    while(1){
        if(*p != ' ')
        {
            temp[j++] = *p;
        }

        // if(*p == '\0')
        //     break;
        // p++;
        if(*p++ == '\0')
            break;
    }

    printf("temp:%s\n",temp);

	return 0;
}