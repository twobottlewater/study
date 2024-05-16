#include "myhead.h"

struct doublelist
{
	//数据域存数据
	int data;
	
	//指针域存下一个数据的首地址
	struct doublelist *next;
	struct doublelist *prev;
};
typedef struct doublelist DoubleList;

//把头节点定义成全局变量
struct doublelist *myhead;

int list_init()
{
	myhead=malloc(sizeof(struct doublelist));
	myhead->next=NULL;
	myhead->prev=NULL;
}

//增
int list_add_tail(int newdata)
{
	struct doublelist *p=myhead;
	while(p->next!=NULL)
		p=p->next;
		
	//插入进去
	struct doublelist *newnode=malloc(sizeof(struct doublelist));
	newnode->data=newdata;
	newnode->next=NULL;
	newnode->prev=NULL;
	
	p->next=newnode;
	newnode->prev=p;
	
	return 0;
	
}


//中间插入
int list_add(int newdata,int olddata)
{
	//先找老的数据
	struct doublelist *p=myhead;
	int flag=0;
	while(p->next!=NULL)
	{
		
		if(p->data==olddata)
		{
			struct doublelist *newnode=malloc(sizeof(struct doublelist));
			newnode->data=newdata;
			newnode->next=NULL;
			newnode->prev=NULL;
			//新节点插入p的后面
			newnode->next=p->next;
			p->next=newnode;
			newnode->next->prev=newnode;
			newnode->prev=p;
			p=p->next;
			flag=1;
		}
		else
		p=p->next;
		
	}

	
	//最后一个节点单独判断
	if(p->next==NULL && p->data==olddata)
	{
		struct doublelist *newnode=malloc(sizeof(struct doublelist));
		newnode->data=newdata;
		newnode->next=NULL;
		newnode->prev=NULL;
		p->next=newnode;
		newnode->prev=p;
		flag=1;
	}
		
	if(flag==0)
	{
		printf("你需要插入的数据块\"%d\"不存在\n",olddata);
	}
	return 0;
}


//删一个
int list_delete(DoubleList **head,int deldata)
{

	
	
	 if (*head == NULL) {
        printf("Error: List is empty.\n");
        return -1; // 返回错误码，表示链表为空
    } 
	
	DoubleList* p = *head;
    DoubleList* temp = NULL;
	
	 do {
        if (p->data == deldata) {
            break;
        }
        temp = p;
        p = p->next;
    } while (p != *head); // 注意这里使用的是*p而不是myhead，因为传入的是头结点的指针地址

    // 如果没有找到匹配的数据，则返回错误
    if (p == *head) {
        printf("Error: Data not found in the list.\n");
        return -1; // 返回错误码，表示未找到指定数据
    }

    // 删除找到的节点
    if (p->prev == p) { // 只有一个节点的情况
        *head = NULL;
    } else {
        p->prev->next = p->next;
        p->next->prev = p->prev;
    }

    free(p);
    p = NULL;
	return 0;
}
 
 
 //chatgpt  删
 int list_delete_all(int deldata)
{
    // 找到要删除的节点
    struct doublelist *p = myhead->next; // 从第一个数据节点开始
    while (p != NULL)
    {
        if (p->data == deldata)
        {
            // 删除当前节点
            struct doublelist *temp = p;
            p = p->next; // 先移动到下一个节点，以防止失去指向
            temp->prev->next = temp->next;
            if (temp->next != NULL) // 如果不是尾节点
                temp->next->prev = temp->prev;
            free(temp);
        }
        else
        {
            p = p->next; // 继续向后查找
        }
    }
    return 0;
}
 

//改
//如果链表支持通过键值查找：
struct doublelist* findNodeByKey(struct doublelist* head, int key) {
    struct doublelist* current = myhead;
    do {
        if (current->data == key) {
            return current;
        }
        current = current->next;
    } while (current != myhead);

    return NULL; // 如果没找到返回NULL
}

// 通过键值修改节点数据
void modifyDataByKey(struct doublelist* head, int oldKey, int newData) {
    struct doublelist* targetNode = findNodeByKey(head, oldKey);
    if (targetNode != NULL) {
        targetNode->data = newData;
    } else {
        printf("Error: Node with key %d not found.\n", oldKey);
    }
}




//查
int list_show()
{
	struct doublelist *p=myhead;
	while(p->next!=NULL)
	{
		p=p->next;
		printf("当前节点的数据是: %d\n",p->data);
	}
	return 0;
}



int main()
{
	//初始化双向链表
	list_init();
	
	//尾插数据
	list_add_tail(11);
	list_add_tail(10);list_add_tail(11);
	list_add_tail(11);list_add_tail(11);
	list_add_tail(12);list_add_tail(11);
	list_add_tail(13);list_add_tail(11);
	list_show();
	
	//printf("=======================尾插之后=======================\n");
	//list_show();

	
	/*//list_add(666,9);
 	printf("=======================中间插入之后=======================\n");
	list_show(); */
	
	//删除节点
	//list_delete_all(11);
	//list_delete_all(12);
	list_delete(&myhead,11);
	printf("=======================删除之后=======================\n");
	list_show();
	
	
	
	/* modifyDataByKey(myhead, 10, 7);
	printf("=======================改数据之后=======================\n");
	list_show(); */
	return 0;
}