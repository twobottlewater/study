#include<stdio.h>
int main()
{
	int a[5],b;
    printf("请输入五个数:\n");
    for(int i=0;i<5;i++)
    {
        scanf("%d",&a[i]);
    }
    for(int k=1;k<5;k++)
    {
        for(int j=0;j<5-k;j++)
        {
            if(a[j]>a[j+1])
            {
                int num=a[j];
                a[j]=a[j+1];
                a[j+1]=num;
            }
        }
    }
    printf("最大值为%d 最小值为%d\n",a[4],a[0]);
	printf("由大到小依次为\n%d\n%d\n%d\n%d\n%d\n",a[4],a[3],a[2],a[1],a[0]);
    return 0;
}