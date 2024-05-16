#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


int getMax(int*p,int len) //int*p = arr1   int*p = arr2
{
    int max = p[0];
    for(int i=1; i<len; i++)
    {
        if(max < p[i])
        {
            max = p[i];
        }
    }

    return max;
}

//如果函数的形式参数列表上 写成数组形式，但是实 际上本质是 指针来着
//int p[3][5] 等价于  int (*p)[5]
int getTMax(int p[3][5],int lines,int colums) //int (*p)[5] = buf;
{
    int max = p[0][0];
    for(int j=0; j<lines; j++)
    {
        for(int i=0; i<colums; i++)
        {
            if(max<p[j][i])
            {
                max =p[j][i];
            }
        }
    }

    return max;
}

int getGenTMax(int*p,int lines,int colums) //int (*p)[5] = buf;
{
    int max = *p;

    for(int i=0; i<lines*colums; i++)
    {
        if(max<*(p+i))
        {
            max = *(p+i);
        }
    }

    return max;
}

int main()
{   
    //定义一个接口，实现获取数组中元素最大的一个
    int arr1[5] = {10,33,55,66,34};
    int arr2[10] = {17,78,55,111,34,566};

    printf("%d\n",getMax(arr1,5)); 
    printf("%d\n",getMax(arr2,10)); 

    //做：定义一个接口，实现求数组元素最大值
    int buf[3][5] = {10,56,67,33,555,88,999,11};
    printf("%d\n", getGenTMax(*buf,3,5)); 

    //有没有什么方法可以兼顾到所有的整形二维数组
    int buf1[4][6] = {10,56,67,33,555,88,999,11};  // int(*p)[6] = buf1;
    getGenTMax((int*)buf1,4,6);

	return 0;
}

