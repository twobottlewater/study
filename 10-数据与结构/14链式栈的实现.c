#include "myhead.h"
#include "kernel_list.h"  //内核链表相关的头文件

/*
用单链表实现栈的逻辑__>>链式栈
ps:用尾巴作为栈顶

*/



//用一个结构体来表示链式栈
struct singlelist
{
	//存数据的地方
	int data;
	//指针域
	struct singlelist *next;
	struct singlelist *top;//栈顶
};

struct singlelist *myhead;
//初始化链式
int list_init()
{
	//定义指针
	myhead=malloc(sizeof(struct singlelist));
	//头节点
	myhead->next=NULL;
	myhead->top=NULL;

}

//入栈
int push(int newdata)
{
	struct singlelist *newnode=malloc(sizeof(struct singlelist));
	newnode->next=NULL;
	newnode->top=NULL;
	newnode->data=newdata;
	//要找到链表的尾部
	struct singlelist *p=myhead;
	while(p->next!=NULL)
		p=p->next; //循环结束p就到了尾部
	
	//把新的节点放到尾部
	p->next=newnode; //赋值翻译成指向
	
	//更新栈顶
	myhead->top=newnode;
		return 0;
	
}

//出栈
int pop()
{
	//判断栈是否空了
	if(myhead->top==myhead)
	{
		printf("栈已经空了，无法出栈了!\n");
		return -1;
	}
	//保存栈顶位置元素值
	int temp=myhead->top->data;
	
	//找到链表的尾巴(栈顶)前面一个位置
	struct singlelist *p=myhead;
	while(p->next!=myhead->top)
		p=p->next;
	//删除栈顶节点
	p->next=NULL;
	free(myhead->top);
	//更新栈顶位置
	myhead->top=p;
	return temp;
}

int main()
{
	
int ret;
	//初始化链式栈
	list_init();
	
	//入栈几个数据
	push(10);
	push(11);
	push(12);
	push(13);
	push(14);
	push(15);
	
	while((ret=pop())!=-1)
	{
		printf("目前出栈的数据是：%d\n",ret);
	}
	return 0;
}