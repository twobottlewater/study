#include "myhead.h"
#include "kernel_list.h"  //内核链表相关的头文件

struct goodmsg
{
	char idnum[20]; //运单号
	char starttime[50]; //订单发起时间
	char saddress[30];  //寄送方地址
	char raddress[30];  //收货方地址
	int type; //包裹类型大小
};
struct kernellist //叫做大
//定义结构体来表示内核链表结构体(宿主结构体)
{
	//数据域
	struct goodmsg g;
	//指针域--》做个封装,叫做小结构体
	struct list_head mypoint;
};

struct kernellist *myhead; //全局变量

//初始化内核链表--》初始化头节点
struct kernellist *list_init()
{
	struct kernellist *head=malloc(sizeof(struct kernellist));
	//指针域初始化
	INIT_LIST_HEAD(&(head->mypoint));
	return head;
}

//把准备新的节点也封装函数
struct kernellist *list_create_node(struct goodmsg someg)
{
	struct kernellist *newnode=malloc(sizeof(struct kernellist));
	//数据域初始化
	newnode->g=someg; //结构体可以直接赋值
	//指针域初始化
	INIT_LIST_HEAD(&(newnode->mypoint));
	return newnode;
}

int main()
{
	//定义变量保存用户的选择
	int n;
	//定义结构体变量保存要插入的物流信息
	struct goodmsg tempgood;
	char delnum[20];

	//定义大结构体指针遍历内核链表
	struct kernellist *pos;
	struct kernellist *otherpos;
	
	//初始化内核链表--》初始化头节点
	myhead=list_init();
	while(1)
	{
		printf("请输入你要选择的功能!\n");
		printf("1.插入物流信息!\n");
		printf("2.删除物流信息!\n");
		printf("3.查询物流信息!\n");
		printf("4.退出程序!\n");
		scanf("%d",&n);
		switch(n)
		{
			case 1: //插入物流信息
				printf("请输入要插入的物流单号!\n");
				scanf("%s",tempgood.idnum);
				printf("请输入寄送方地址!\n");
				scanf("%s",tempgood.saddress);
				printf("请输入收货方地址!\n");
				scanf("%s",tempgood.raddress);
				printf("请输入包裹类型!\n");
				scanf("%d",&(tempgood.type));
				//获取当前系统时间
				time_t mytime=time(NULL);
				strcpy(tempgood.starttime,ctime(&mytime));
				//尾插节点
				struct kernellist *node=list_create_node(tempgood);
				list_add_tail(&(node->mypoint),&(myhead->mypoint));
				break;
			case 2:  //删除物流信息
				printf("请输入要删除的订单号!\n");
				scanf("%s",delnum);
				list_for_each_entry_safe(pos,otherpos,&(myhead->mypoint),mypoint)
				{
					if(strcmp(pos->g.idnum,delnum)==0)
						list_del(&(pos->mypoint));
				}
				break;
			case 3:  //查询物流信息
				list_for_each_entry(pos,&(myhead->mypoint),mypoint)
				{
					printf("运单编号: %s\n",pos->g.idnum);
					printf("订单发起时间: %s\n",pos->g.starttime);
					printf("寄送方地址: %s\n",pos->g.saddress);
					printf("收货方地址: %s\n",pos->g.raddress);
					printf("包裹类型: %d\n",pos->g.type);
					printf("\n");
					
				}
				break;
			case 4: //退出程序
				return 0;
				break;
		}
	}
}
 