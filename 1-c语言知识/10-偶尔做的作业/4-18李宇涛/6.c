#include <stdio.h>
/*6、将字符串中的重复字符删除，并输出新字符串。 
例如： gooogggle --->  输出 gole*/

int main() 
{
    char str1[100] = "gooogggle";
    int len = strlen(str1);
    for (int i = 0; i < len; i++) 
    {
        for (int j = i + 1; j < len;) 
        {
            if (str1[i] == str1[j])
            {
            for (size_t k = j; k < len; k++)
            {
                char temp;
                str1[k]= str1[k+1];
            }
            len--;
            }
            else
            {
                j++;
            }
        }
    }
	
   
    printf("改好后的字符串: %s\n", str1);

    return 0;
}
