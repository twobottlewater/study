#include <stdio.h>

//显示数据
void printf_data(int *arr, int len)
{
  int i;
  for(i=0; i<len; i++)
  {
    printf("%d\t", arr[i]);
  }  
  printf("\n");
}

void insertsort(int buf[],int n)
{
	int i,j,temp;
	//下标0已经是有序序列，所有循环从下标1开始(无序序列)
	for(i=1; i<n; i++)  
	{
		if(buf[i]<buf[i-1])
		{
			//把i位置的数据备份
			temp=buf[i];
			for(j=i-1; buf[j]>temp && j>=0; j--) //把前面排好序的挪动，找到temp存放的位置
				buf[j+1]=buf[j];
			
			buf[j+1]=temp;
		}
	}
}


int main(void)
{
  int i, len;
  int arr[10];

  len = sizeof(arr)/sizeof(int);

  printf("请输入10个整数:\n");

  for(i=0; i<10; i++)
  {
    scanf("%d", &arr[i]);
  }

  printf("排序前数据:\n");

  printf_data(arr, len);

  insertSort(arr, len);

  printf("排序后数据:\n");

  printf_data(arr, len);

  return 0;
  //hh
}