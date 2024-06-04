#include <stdio.h>
#include <string.h>

 int main()
 { 
     int i,j,k;
     char buf[100]={0};

     printf("请输入一个字符串\n");
     scanf("%s",buf);

    for (i=0;i<strlen(buf);i++)
    {
          for (j=i+1;j<strlen(buf); j++)
          {
              if (buf[i]==buf[j])
              {
               for(k=j;k<strlen(buf);k++)
               {
                    buf[k]=buf[k+1];
               }
               j--;
              
              }
              
          }
          
     
    }
      printf("现在结果是：%s\n",buf);
	
      return 0;
     }
