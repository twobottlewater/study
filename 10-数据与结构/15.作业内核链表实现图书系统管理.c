#include "myhead.h"
#include "kernel_list.h"  //内核链表相关的头文件



struct book
{
	char name[20]; //书名
	char authorname[20]; //作者名
	float price;  //价格
	int num; //这本书总的数量
};

struct kernellist //叫做大
//定义结构体来表示内核链表结构体(宿主结构体)
{
	//数据域
	struct book b;
	//指针域--》做个封装,叫做小结构体
	struct list_head mypoint;
};

struct kernellist *myhead; //全局变量

//内核链表的初始化
struct kernellist *list_init()
{
	struct kernellist *head=malloc(sizeof(struct kernellist));
	INIT_LIST_HEAD(&(head->mypoint));
	return head;
	
}



//封装一个函数准备新的节点
struct kernellist *list_create_node(struct book somebook)
{
	struct kernellist *newnode=malloc(sizeof(struct kernellist));
	//初始化数据域
	newnode->b=somebook;
	//指正域的初始化
	INIT_LIST_HEAD(&(newnode->mypoint));
	return newnode;
	
	
}



int main()
{
	//定义变量保存用户的选择
	int n,m;
	//定义结构体变量保存要插入的书籍信息
	struct book tempbook;
	//定义数组存放要删除的书籍名字
	char delname[20];
	//定义数组存放要修改的书籍名字
	char oldname[20];
	char newname[20];
	char newauthorname[20];
	float newprice;
	int newnum;
	//定义大结构体指针遍历内核链表
	struct kernellist *pos;
	struct kernellist *otherpos;
	//初始化内核链表--》初始化头节点
	myhead=list_init();
	while(1)
	{
		printf("请输入你要选择的功能!\n");
		printf("1.插入书籍信息!\n");
		printf("2.删除书籍信息!\n");
		printf("3.修改书籍信息!\n");
		printf("4.查询书籍信息!\n");
		printf("5.退出程序!\n");
		scanf("%d",&n);
		switch(n)
		{
			case 1: //插入书籍信息
				printf("请输入要插入的书籍名称!\n");
				scanf("%s",tempbook.name);
				printf("请输入要插入的书籍作者名字!\n");
				scanf("%s",tempbook.authorname);
				printf("请输入要插入的书籍价格!\n");
				scanf("%f",&(tempbook.price));
				printf("请输入要插入的书籍数量!\n");
				scanf("%d",&(tempbook.num));
				//尾插节点
				struct kernellist *node=list_create_node(tempbook);
				list_add_tail(&(node->mypoint),&(myhead->mypoint));
				break;
			case 2:  //删除书籍信息
				printf("请输入你要删除的书籍名字!\n");
				scanf("%s",delname);
				//遍历内核链表，找到要删除的书籍
				list_for_each_entry_safe(pos,otherpos,&(myhead->mypoint),mypoint)
				{
					if(strcmp(pos->b.name,delname)==0)
					{
						list_del(&(pos->mypoint));
					}
				}
				break;
			case 3:  //修改书籍信息
				printf("请输入你要修改的书籍名字!\n");
				scanf("%s",oldname);
				printf("请输入你要修改这本书籍的什么信息1.书名,2.作者,3.价格,4.书籍数量?！\n");
				scanf("%d",&m);
				switch(m)
				{
					case 1: //修改书名
						printf("请输入新的书名!\n");
						scanf("%s",newname);
						//遍历内核链表，找到要修改的书籍
						list_for_each_entry(pos,&(myhead->mypoint),mypoint)
						{
							if(strcmp(pos->b.name,oldname)==0)
								strcpy(pos->b.name,newname);
						}
						break;
					case 2: //修改作者
					    printf("请输入新的作者名字!\n");
						scanf("%s",newauthorname);
						//遍历内核链表，找到要修改的书籍
						list_for_each_entry(pos,&(myhead->mypoint),mypoint)
						{
							if(strcmp(pos->b.name,oldname)==0)
								strcpy(pos->b.authorname,newauthorname);
						}
						break;
					case 3: //修改价格
						printf("请输入新的价格!\n");
						scanf("%f",&newprice);
						//遍历内核链表，找到要修改的书籍
						list_for_each_entry(pos,&(myhead->mypoint),mypoint)
						{
							if(strcmp(pos->b.name,oldname)==0)
								pos->b.price=newprice;
						}
						break;	
					case 4: //修改数量
						printf("请输入新的书籍数量!\n");
						scanf("%d",&newnum);
						//遍历内核链表，找到要修改的书籍
						list_for_each_entry(pos,&(myhead->mypoint),mypoint)
						{
							if(strcmp(pos->b.name,oldname)==0)
								pos->b.num=newnum;
						}
						break;	
				}
				break;
			case 4:  //查询书籍信息
				list_for_each_entry(pos,&(myhead->mypoint),mypoint)
				{
					printf("书名: %s 作者: %s 价格: %f 数量: %d\n",pos->b.name,pos->b.authorname,pos->b.price,pos->b.num);
				}
				break;
			case 5: //退出程序
				return 0;
				break;
		}
	}
	return 0;
}