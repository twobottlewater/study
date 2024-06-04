#include<stdio.h>
#include <stdbool.h>
int main()
{
    /*
    4、华为笔试题，输入google,输出 gole（过滤相同的字母）
char str=[32] = {'\0'};
scanf("%s", str);  //暂时不考虑空格#include <stdio.h>
    */

   char input[20] = {0}; //输入的字符串
   char str[20] = {0};  //去掉重复的保存到这里

   while(1)
   {
        memset(input,0,20);
        memset(str,0,20);

        printf("请输入字符串:");
        scanf("%s",input); 

        int i=0;
       while(1)
       {
            if( *(input + i) == '\0')
                break;

            //遍历str数组，跟上面的拿出来的字符进行比较
            int j=0;
            bool flag=true; //如果为true表示，当前字符跟下面的字符没有重复

            while(1)
            {
                if(*(str+j) == '\0')
                    break;

                if(*(str+j) == *(input+i))
                {
                    flag = false;
                    break;
                }
                j++;
            }

            if(flag == true)
            {
                *(str + j) = *(input + i);
            }

            i++;
       }

       printf("str:%s\n",str);
   }

    

	return 0;
}