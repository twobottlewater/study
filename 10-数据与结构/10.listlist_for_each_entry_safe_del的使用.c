#include "myhead.h"
#include "kernel_list.h"  //内核链表相关的头文件

//跟双向循环链表一样，搞个结构体来表示内核链表
struct kernellist //叫做大结构体(宿主结构体)
{
	//数据域
	int data;
	//指针域--》做个封装,叫做小结构体
	struct list_head mypoint;
};

//初始化内核链表--》初始化头节点
struct kernellist *list_init()
{
	struct kernellist *head=malloc(sizeof(struct kernellist));
	//指针域初始化
	INIT_LIST_HEAD(&(head->mypoint));
	return head;
}

//尾插--》不需要自己写了，内核链表把尾插代码写好了

int main()
{
	//初始化内核链表--》初始化头节点
	struct kernellist *myhead=list_init();
	

	//准备新的节点
	struct kernellist *node1=malloc(sizeof(struct kernellist));
	node1->data=10;
	//指针域初始化
	INIT_LIST_HEAD(&(node1->mypoint));
	
	struct kernellist *node2=malloc(sizeof(struct kernellist));
	node2->data=11;
	//指针域初始化
	INIT_LIST_HEAD(&(node2->mypoint));
	
	struct kernellist *node3=malloc(sizeof(struct kernellist));
	node3->data=12;
	//指针域初始化
	INIT_LIST_HEAD(&(node3->mypoint));
	
	struct kernellist *node4=malloc(sizeof(struct kernellist));
	node4->data=13;
	//指针域初始化
	INIT_LIST_HEAD(&(node4->mypoint));
	
	//演示list_add_tail的用法
	//功能1：把新的节点尾插到myhead代表的链表的尾部
	list_add_tail(&(node1->mypoint),&(myhead->mypoint));
	list_add_tail(&(node2->mypoint),&(myhead->mypoint));
	list_add_tail(&(node3->mypoint),&(myhead->mypoint));
	
	
	//验证你尾插是否成功
	struct kernellist *p;  
	struct kernellist *n; 
	list_for_each_entry(p,&(myhead->mypoint),mypoint)
	{
		printf("删除之前当前遍历的节点存放的数据是: %d\n",p->data);
	}
	
	list_for_each_entry_safe(p,n,&(myhead->mypoint),mypoint) 
	{
		//判断现在节点是不是10
		if(p->data==10)
			list_del(&(p->mypoint)); //删除节点
	}
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("============删除之后===============\n");
	list_for_each_entry(p,&(myhead->mypoint),mypoint)
	{
		printf("删除之后当前遍历的节点存放的数据是: %d\n",p->data);
	}
	

}