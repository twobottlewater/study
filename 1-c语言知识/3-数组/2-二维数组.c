#include<stdio.h>

int main()
{
    //二维数组
    // int array[4][5] = {{11,22,33,44,55},
    //                    {66,77,88,99,10},
    //                    {3,4,5,6,7},
    //                    {13,14,15,16,17}};
    // int array[4][5] = {11,22,33,44,55,
    //                    66,77,88,99,10,
    //                    3,4,5,6,7,
    //                    13,14,15,16,17};
    // int array[4][5] = {{11,22,33},44,55,
    //                    66,77};
    int array[4][5] = {11,22,33,44,55,
                       66,77,88,99,10,
                       3,4,5,6,7,
                       13,14,15,16,17};

    for(int j=0; j<4; j++) //有4个一维数组
    {
        for(int i=0; i<5; i++)//每个一维数组有5个元素
        {
            printf("%d\t",array[j][i]);
        }

        printf("\n");
    }

    //printf("%d\n",*(&array[0][4]+1));

    for(int j=0; j<4; j++) //行
    {
        for(int i=0; i<5; i++) //列
        {
            printf("%p(%d)\t",&array[j][i],array[j][i]);
        }

        printf("\n");
    }

    printf("array addr:%p\n",array);
    printf("array+1 addr:%p\n",array+1);

    printf("array[0][0] addr:%p\n",&array[0][0]);
    printf("array[0][0]+1 addr:%p\n",&array[0][0]+1);
	return 0;
}