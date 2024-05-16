#include "myhead.h"
#include "kernel_list.h"


struct  kernellist//大结构体
{
	//数据域
	int data;
	//指针域
	struct list_head mypoint;
	
};

//初始化内核链表-->>初始化头节点
struct kernellist *list_init()
{
	struct kernellist  *head=malloc(sizeof(struct kernellist));
	//指针域初始化
	INIT_LIST_HEAD(&(head->mypoint));
	return head;
	
}


int main()
{
	printf("大结构体的大小: %ld\n",sizeof(struct kernellist));
	//初始化内核链表--》初始化头节点
	struct kernellist *myhead=list_init();
	//添加新的节点
	struct kernellist *node1=malloc(sizeof(struct kernellist));
	node1->data=10;
	//指针域初始化
	INIT_LIST_HEAD(&(node1->mypoint));
	
	//添加新的节点
	struct kernellist *node2=malloc(sizeof(struct kernellist));
	node2->data=11;
	//指针域初始化
	INIT_LIST_HEAD(&(node2->mypoint));
	
	
	
	//添加新的节点
	struct kernellist *node3=malloc(sizeof(struct kernellist));
	node3->data=12;
	//指针域初始化
	INIT_LIST_HEAD(&(node3->mypoint));
	
		
	//添加新的节点
	struct kernellist *node4=malloc(sizeof(struct kernellist));
	node4->data=13;
	//指针域初始化
	INIT_LIST_HEAD(&(node4->mypoint));
	
	
	struct kernellist *node5=malloc(sizeof(struct kernellist));
	node5->data=14;
	//指针域初始化
	INIT_LIST_HEAD(&(node5->mypoint));
	
	
	//功能1 尾插功能展示
	list_add_tail(&(node1->mypoint),&(myhead->mypoint));
	list_add_tail(&(node2->mypoint),&(myhead->mypoint));
	list_add_tail(&(node3->mypoint),&(myhead->mypoint));
	//功能2  把5插到2前面
	list_add_tail(&(node5->mypoint),&(node2->mypoint));
	
	
	
	
	
	
	//验证你尾插是否成功
	struct kernellist *p;  //野指针，p没有看到往后挪动
	list_for_each_entry(p,&(myhead->mypoint),mypoint)
	{
		printf("当前遍历的节点存放的数据是: %d\n",p->data);
	}
	
	
	
	
	
	
	
	//定义另外一个--》初始化头节点
	struct kernellist *nomyhead=list_init();
	//准备新的节点
	struct kernellist *node10=malloc(sizeof(struct kernellist));
	node110->data=10;
	//指针域初始化
	INIT_LIST_HEAD(&(node10->mypoint));
	return 0;
	
	
	list_for_each_entry(p,&(nomyhead->mypoint),nomypoint)
	{
		printf("当前遍历的节点存放的数据是: %d\n",p->data);
	}
	
}