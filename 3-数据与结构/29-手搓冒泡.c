#include <stdio.h>
#include <stdlib.h>


void bublleSort(int arr[],int n) 
{
   
	int i, j, temp;
	for(i=0;i<n-1;i++)
	{	
		printf("i is %d\n",i);  ///0000
		for(j=0;j<n-1-i;j++)
		{
			printf("j is %d\n",j);  ///0000
			if(arr[j]>arr[j+1])
			{
				temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
		
	}

}

int main()
{
	int arr[10]={99,88,7,55,8,9,54,66,58,952};
	int n=10;


	printf("原始数组：\n");
    for (int i = 0; i < n; i++)
	{
       printf("%d ", arr[i]);
    }
    printf("\n");
    
    bublleSort(arr,10);
    printf("排序后的数组：\n");
    for (int i = 0; i < n; i++) 
	{
     printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
	
}