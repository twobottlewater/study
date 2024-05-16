#include "myhead.h"

struct singlelist
{
	//数据域存数据
	int data;
	
	//指针域存下一个数据的首地址
	struct singlelist *next;
};
struct singlelist *myhead;
//定义一个单向循环链表

//初始化一个单向循环链表
int list_init()
{
	//定义指针
	struct singlelist *myhead=malloc(sizeof(struct singlelist));
	//指针指向自己
	myhead->next=myhead;
	
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
	struct singlelist *p=myhead;
	while(p->next!=myhead)
		p=p->next;
		
	p->next=newnode;
	newnode->next=myhead;
	//找到了倒数第二个节点的next就写最后节点的地址上去
	
	return 0;
}





//单向循环链表的中间插入--》把newdata插入olddata代表节点后面
/*
	情况1：如果olddata有多个，要求每个olddata的后面都插入newdata
	情况2：olddata不存在
*/
int list_add(int newdata,int olddata)
{
	//先找到olddata
	struct singlelist *p=myhead;
	int flag=0;
	
	while(p->next!=myhead)
	{
		if(p->data==olddata)
		{
			//准备新的节点
			struct singlelist *newnode=malloc(sizeof(struct singlelist));
			//存个newdata
			newnode->data=newdata;
			newnode->next=NULL; 
			newnode->next=p->next;
			p->next=newnode;
			flag=1;
			p=newnode->next;
		}
		else{
			p=p->next;
		}
	}
	if(p->data==olddata && p->next==myhead)
		{
			struct singlelist *newnode=malloc(sizeof(struct singlelist));
			//存个newdata
			newnode->data=newdata;
			newnode->next=myhead; 
			p->next=newnode;
			flag=1;
			p=newnode->next;
		}
	if(flag==0)
		printf("%d在链表中根本不存在\n",olddata);
			
	return 0;
} 



//改
int list_update(int olddata,int newdata)
{
	struct singlelist *p=myhead;
	while(p->next!=myhead)
	{
		if(p->data==olddata)
			p->data=newdata;
		p=p->next;
	}
	//把最后一个位置的节点判断
	if(p->data==olddata)
			p->data=newdata;
	return 0;
} 


//删

/*
	情况1：如果deldata有多个，要求每个deldata都删除
	情况2：deldata不存在
*/
int list_delete(int deldata)
{	
	//定义两个指针，一前一后来编译链表
	struct singlelist *p=myhead->next;
	struct singlelist *q=myhead;
	//定义变量标记deldata是否存在
	int flag=0;

	while(p!=myhead)
	{
		if(p->data==deldata)
		{
			flag=1;
			//删除p指向的节点
			q->next=p->next;  //q现在可能是头  没有东西  接住p的next
			p->next=NULL;		//释放掉p因为p是要删除的东西
			free(p);  //p变成了野指针了
			p=q->next; //很重要    p拿住q的next
		}
		
		else
		{
			p=p->next;
			q=q->next;
		}
		
	}
	if(flag==0)
	{
		printf("%d是不存在的！\n",deldata);
		return -1;
	}	
	return 0;
} 

//查
int list_show()
{
	struct singlelist *p=myhead;
	while(p->next!=myhead)
	{
		p=p->next; //循环结束p就到了尾部
		//打印当前p指向的那个节点里面的内容
		printf("目前遍历的数据是: %d,该节点的首地址是: %p\n",p->data,p);
	
	}
	return 0;	
}



int main()
{
	myhead=list_init();
	list_add_tail(2);
	list_add_tail(3);list_add_tail(3);list_add_tail(3);list_add_tail(3);
	//list_add(78,2);

	//list_add(105,3);
	list_show();
	
	//list_add(22,3);
	//list_add(3,6666);
	printf("====================增加之后=====================\n");
	list_show();
	
	list_delete(3);
	printf("====================删除后=====================\n");
	list_show();
	
	list_update(2,6666);
	printf("====================修改后=====================\n");
	list_show();
	//lsit_delete(78);
	//list_show();
	
	return 0;
	
}