#include <stdio.h>   
#include <stdlib.h>
int getMax(int arr[][5])
{	
	int max = arr[0][0]; // 初始化最大值为数组第一行的第一个元素
    int rows = sizeof(arr) / sizeof(arr[0]); // 获取行数
    int cols = sizeof(arr[0]) / sizeof(arr[0][0]); // 获取列数

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (arr[i][j] > max) {
                max = arr[i][j]; // 如果找到更大的值，则更新最大值
            }
        }
    }
	return max;
}

int main() 
{
	int a[3][5]={10,56,67,33,555,88,999,11};
	int ret=getMax(a);
	printf("最大值是：%d",ret);
	return 0;
}