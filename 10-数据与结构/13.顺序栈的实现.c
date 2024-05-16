#include "myhead.h"
#include "kernel_list.h"  //内核链表相关的头文件

/*
用顺序表来实现栈的逻辑
用一个栈来存整数

*/



//用一个结构体来表示顺序栈
struct seqstack
{
	//存数据的地方
	int buf[100];
	//定义一个变量来标记目前栈顶的位置
	int top;

	
};

struct seqstack *mystack;


//顺序栈的初始化
struct seqstack *stack_init()
{
	struct seqstack *stack=malloc(sizeof(struct seqstack));
	//最开始没有东西给他一个-1标志位
	stack->top=-1;
	return stack;
}


//入栈

int push(int newdata)
{
	//更新栈顶
	mystack->top++;
	//把数据存到栈顶的位置
	mystack->buf[mystack->top]=newdata;
	return 0;
	
}
//出栈
int pop()
{
	//存着栈顶的数据
	
	int temp= mystack->buf[mystack->top];
	//更新栈顶的位置
	mystack->top--;
	return temp;
	
}


//栈的销毁
int stack_uninit()
{
	free(mystack);
	return 0;
	
	
}


int main()
{
	
	mystack    =stack_init();
	//表演入栈
	push(10);
	push(11);
	push(12);
	push(13);
	
	//出栈
	for(int i=0;i<4;i++)
	{
		
		printf("出栈的数据是:%d\n",pop());
	}
	stack_uninit();
	return 0;
}