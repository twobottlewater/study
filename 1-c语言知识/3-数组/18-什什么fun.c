#include <stdio.h>
 
int fun(int a[][3])
     {
        int i,j,sum=0;
        for(i=0; i<3; i++)
          for(j=0; j<3; j++)
          {
              if(i==j)
                 sum=sum+a[i][j];  //a[0][0] a[1][1] a[2][2]
          }
        return sum;
     }
     int main()
     {
        int a[3][3]={1,2,3,1,2,3,1,2,3},sum;
        sum=fun(a);
        printf("sum=%d\n",sum);  //6
     }