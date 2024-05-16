#include <stdio.h>
#include <string.h>

 int main()
 { 
//       char time[100]="2023/12/30";
//       //第一次遇到'/'就切割
//      char *p=strtok(time,"/");
//      printf("%s\n",p);

//     //第二次切割
//     p=strtok(NULL,"/");
//     printf("sec is %s\n",p);
    
//     //第三次切割
//     p=strtok(NULL,"/");
//     printf("thr is %s\n",p);
     char time[100]="2023/12/30 19:39:37";
     char *p=strtok(time,"/ :");
     printf("%s\n",p);
     while ((p=strtok(NULL,"/ :"))!=NULL)
     {
          
          printf("%s\n",p);
          /* code */
     }
     
      return 0;
     }