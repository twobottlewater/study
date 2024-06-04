#include "myhead.h"
#include "bitree.h"
/*
	用顺序表来表示队列
*/
#define N 10 
struct seqqueue
{
	NODE *buf[N]; //数组存放真实的数据
	int head; //标记队首
	int tail; //标记对尾
};

struct seqqueue *myqueue;
//初始化顺序队列
struct seqqueue *seqqueue_init()
{
	struct seqqueue *seq=malloc(sizeof(struct seqqueue));
	seq->head=0;  //队首位置固定是下标0
	seq->tail=-1; //队尾位置
	return seq;
}

//入队--》永远都是从队尾入队
int myin_queue(NODE *newdata)
{
	//判断队列是否满了
	if(myqueue->tail>=N-1)
	{
		printf("队列满了!\n");
		return -1;
	}
	//更新队尾位置
	myqueue->tail++;
	//保存队尾数据
	myqueue->buf[myqueue->tail]=newdata;
	return 0;
}

//判断队列是否空了
int if_empty()
{
	//判断队列是否空了
	if(myqueue->tail<0)
	{
		printf("队列空了!\n");
		return -1;
	}
	return 0;
}
//出队
NODE *myout_queue()
{
	if(if_empty()==-1)
	{
		return NULL;
	}
	int i;
	//把队首元素保存
	NODE *temp=myqueue->buf[myqueue->head];
	//后面往前挪动
	for(i=0; i<myqueue->tail; i++)
		myqueue->buf[i]=myqueue->buf[i+1];
	//更新队尾位置
	myqueue->tail--;
	return temp;
}

