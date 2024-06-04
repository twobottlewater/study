#include "myhead.h"
#include "kernel_list.h"  //内核链表相关的头文件

/*
	用顺序表来表示队列
*/
#define N 10 
struct seqqueue
{
	int buf[N]; //数组存放真实的数据
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

//入队  永远是队尾入队
int in_queue(int newdata)
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


//出队
int out_queue()
{
	//判断队列是否空了
	if(myqueue->tail<0)
	{
		printf("队列空了!\n");
		return -1;
	}	
	int i;
	//把队首元素保存
	int temp=myqueue->buf[myqueue->head];
	//后面往前挪动
	for(i=0; i<myqueue->tail; i++)
		myqueue->buf[i]=myqueue->buf[i+1];
	//更新队尾位置
	myqueue->tail--;
	return temp;

}




int main()
{
	//初始化顺序队列
	myqueue=seqqueue_init();
	int ret;
	//入队几个数据
	in_queue(10);
	in_queue(11);
	in_queue(12);
	in_queue(13);
	in_queue(14);
	in_queue(15);
	in_queue(16);
	//出队几个数据
	while((ret=out_queue())!=-1)
	{
		printf("目前出队的数据是: %d\n",ret);
	}
	
	return 0;
}