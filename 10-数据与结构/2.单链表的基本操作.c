#include "myhead.h"

struct singlelist
{
	//数据域存数据
	int data;
	
	//指针域存下一个数据的首地址
	struct signlelist *next;
};
struct singlelist *mylist;
//定义一个链表

//初始化一个链表
struct singlelist *list_init()
{
	//定义指针
	mylist=malloc(sizeof(struct singlelist));
	//第一个成员初始化为1
	mylist->data=1;
	//指针指向什么地方
	mylist->next=NULL;
	return mylist;
	
}

//增   尾插地增
int list_add_tail(int newdata)
{
	struct singlelist *newnode=malloc(sizeof(struct singlelist));
	//存newdata
	newnode->data=newdata;
	//设置新指针
	newnode->next=NULL;
	//把新的数据地址写在上一个数据的next上
	struct singlelist *p=mylist;
	while(p->next!=NULL)
		p=p->next;
		
	p->next=newnode;
	//找到了倒数第二个节点的next就写最后节点的地址上去
	
	return 0;
}

//单链表的中间插入--》把newdata插入olddata代表节点后面
/*
	情况1：如果olddata有多个，要求每个olddata的后面都插入newdata
	情况2：olddata不存在
*/

int list_add(int newdata,int olddata)
{
	//先找到olddata
	struct singlelist *p=mylist;
	while(p->next!=NULL)
	{
		if(p->data==olddata)
			break;
		p=p->next;
	}
	//准备新的节点
	struct singlelist *newnode=malloc(sizeof(struct singlelist));
	//把newdata存放起来
	newnode->data=newdata;
	//指针指向哪里呢？
	newnode->next=NULL; 
	
	
	//整理指针关系
	newnode->next=p->next;
	//这个p的next在上一步中找到是老数据的后一位位置
	//问题是把newdata插入olddata代表节点后面
	p->next=newnode;
	return 0;
	
	
}

int list_show()
{
	struct singlelist *p=mylist;
	while(p!=NULL)
	{
		//打印当前p指向的那个节点里面的内容
		printf("目前遍历的数据是: %d,该节点的首地址是: %p\n",p->data,p);
		p=p->next; //循环结束p就到了尾部
	}
	
	return 0;	
}
//删除
int lsit_delete(int deldata)
{
	struct singlelist *p=mylist->next;
	struct singlelist *q=mylist;
	if(q->data==deldata) //头节点里面就是要删除的数据
	{
		//更新头节点--》后面的节点现在变成了头节点
		mylist=p;
		q->next=NULL;
		free(q);
		return 0;
		
	}
	while(p->next!=NULL){
		if(p->data==deldata)
			break;
		else
		{
			p=p->next;
			q=q->next;
		}
		
	}
	//删除p指向的节点
	q->next=p->next;
	p->next=NULL;
	free(p);
	return 0;
}



int main()
{
	mylist=list_init();
	list_add_tail(2);
	list_add_tail(3);
	list_add(78,2);

	list_add(105,3);
	list_show();
	printf("====================删除后=====================\n");
	lsit_delete(78);
	list_show();
	
	return 0;
	
}