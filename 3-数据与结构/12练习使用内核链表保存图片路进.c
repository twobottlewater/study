#include <stdio.h>

void slectsort(int buf[],int n)
{
    int i,j,min,temp;
        for(i=0;i<n-1;i++)
        {
            min=i;

            for (j = i+1; j < n; j++)
            {
                if(buf[j]<buf[i])
                {
                    min=j;
                }
                /* code */
            }
            if (min!=i)
            {
                temp=buf[min];
                buf[min]=buf[i];
                buf[i]=temp;
                /* code */
            }
        }

}
int main()
{
   
    int buf[6]={10,98,56,663,66};
    slectsort(buf[6],6)
    for (size_t i = 0; i < 6; i++)
    {
        printf("数组中的元素是什么？：：：：%d",buf[i]);
        /* code */
    }
   return 0; 
}