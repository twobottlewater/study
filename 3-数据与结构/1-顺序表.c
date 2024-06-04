#include<stdio.h>
#include <stdlib.h>

//顺序表的管理结果体
typedef struct {
    int *arr;  //连续堆空间的起始地址
    int index; //最后一个元素的位置  实际存的数据个数
    int size ; //最大能存的元素的总个数
}SeqManager_t;


//顺序表---线性结构（一对一）的一种 
/*
优点：由于存储数据的内存空间是连续的，所以访问的效率非常高
缺点：
1、中间插入或者中间删除需要成片地移动数据，效率非常低
2、在存储数据之前，该顺序表 的内存空间就得固定好
3、需要申请成片的内存空间
*/
//定义一个结构体变量
SeqManager_t seq;

//顺序表
void initSeq(int sz)
{
    seq.size = sz;
    //int array[10];
    seq.arr = calloc(sz,sizeof(int));
}

//插入数据
void push(int data)
{
    seq.arr[seq.index] = data;

    seq.index++;
}
//删除数据
void pop(int data)
{
    for(int i=0; i<seq.index; i++) // 0  1  2  3
    {
        if(seq.arr[i] == data)
        {
            for(int j=i; j<seq.index; j++)
            {
                seq.arr[j] = seq.arr[j+1];
            }
            
            break;
        }
    }

    seq.index--;
}

int main()
{
    //初始化顺序表
    initSeq(10);

    push(66);
    push(77);
    push(88);
    push(99);

    for(int i=0; i<seq.index; i++)
    {
        printf("%d\n",seq.arr[i]);
    }

    pop(77);

    for(int i=0; i<seq.index; i++)
    {
        printf("%d\n",seq.arr[i]);
    }

    return 0;
}